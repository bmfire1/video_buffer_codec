#pragma once
#include "opencv2/opencv.hpp"
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <queue>
#include <sys/time.h>


extern "C" {
#include "libavutil/opt.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/time.h"
#include "libswscale/swscale.h"
#include "libavutil/mathematics.h"
#include "libavutil/audio_fifo.h"
#include "libavutil/imgutils.h"
#include "libavutil/file.h"
}

inline long GetTimestampMs(){
  struct timeval t;
  gettimeofday(&t, nullptr);
  return t.tv_sec*1000 + t.tv_usec/1000;
}

size_t buffer_size = 1024 * 32;

FILE *fp_open = nullptr;

int read_file_cb(void *opaque, uint8_t *buf, int buf_size){
  if(!feof(fp_open)){
      int true_size=fread( buf, 1, buf_size, fp_open);
      buf += true_size;
      std::cout<<"[read_buffer]buf_size:"<<buf_size<<":read_size:"<<true_size<<std::endl;
      return true_size;
    }else{
      printf("file end.\n");
      return -1;
    }
}

int64_t seek_file(void *opaque, int64_t offset, int whence) {
  std::cout<<__LINE__<<":offset:"<<offset<<",whence:"<<whence<<std::endl;
  if (whence == SEEK_SET && fseek(fp_open, offset, SEEK_SET) == 0) {
      std::cout<<"[seek]offset:"<<offset<<std::endl;
      return offset;
    }
  return -1;
}


struct video_buf{
  uint8_t *ptr;
  uint8_t *org_ptr;
  size_t size;
  size_t total_size;
};

//copy a buf_size block from input_buffer at a certain postion
int read_buffer_cb(void *opaque, uint8_t *buf, int buf_size){
  struct video_buf *bd = (struct video_buf*) opaque;

  int ret_size = FFMIN(buf_size, bd->size);
  if (!buf_size){
      printf("no buf_size pass to this func,%d, %d\n.",buf_size,bd->size);
      printf("end buffer.\n");
      return -1;
    }
  //  printf("ptr:%p in io.buffer size:%zu bz:%zu\n", bd->ptr, bd->size, buf_size);
  /* copy internal buffer data to buf */
  memcpy(buf, bd->ptr, ret_size);
  bd->ptr += ret_size;
  bd->size -= ret_size;
//  std::cout<<"[read_buffer]need_size:"<<buf_size<<":read_size:"<<ret_size<<std::endl;
  return ret_size;
}

//seek the input_buffer
int64_t seek_cb(void *opaque, int64_t offset, int whence) {
  struct video_buf *bd = (struct video_buf*) opaque;
//  std::cout<<"[seek_cb]offset:"<<offset<<",whence:"<<whence<<std::endl;
  int ret = -1;
  switch (whence) {
    case AVSEEK_SIZE:
      ret = bd->total_size;
      break;
    case SEEK_SET:
      bd->ptr = bd->org_ptr + offset;
      bd->size = bd->total_size - offset;
      ret = offset;
      break;
    }
  return ret;

}



int main(int argc, char* argv[])
{
  char* input_path = "../images/test.mp4";
  if(argc==2){
      input_path = argv[1];
      //      std::cout<<"video file path:"<<input_path<<std::endl;
    }

  AVFormatContext	*pFormatCtx;
  AVCodecContext	*pCodecCtx;
  AVCodec			*pCodec;
  AVIOContext       *avio;
  AVFrame	        *pFrame;
  AVPacket          *packet;

  std::mutex          m_mutex_FormatCtx;
  int                 m_nFrameCount = 0;
  struct SwsContext   *imgrgb_convert_ctx;

  int               videoindex;
  int				i;
  int               ret;
  int               got_picture;
  size_t            y_size;
  unsigned char     *aviobuffer;
  FILE              *fp_yuv;


  fp_open = fopen(input_path, "rb+");
  fp_yuv  = fopen("../result/output.yuv", "wb+");

  //load file to buffer
  uint8_t * buf = nullptr;
  size_t buf_size = 0;
  ret = av_file_map(input_path, &buf, &buf_size, 0, nullptr);
  struct video_buf bd  = {0};
  bd.ptr = buf;
  bd.size = buf_size;
  bd.org_ptr = buf;
  bd.total_size = buf_size;

  av_register_all();
  pFormatCtx = avformat_alloc_context();

  aviobuffer=(unsigned char *)av_malloc(buffer_size);
//  avio = avio_alloc_context(aviobuffer, buffer_size, 0 ,nullptr,read_buffer,nullptr,&seek);
  //read buffer
    avio = avio_alloc_context(aviobuffer, buffer_size, 0 , &bd, read_buffer_cb , nullptr, &seek_cb);

  /* Open an input stream and read the header. */
  pFormatCtx->pb = avio;
//  pFormatCtx->flags = AVFMT_FLAG_CUSTOM_IO;
  if(avformat_open_input(&pFormatCtx, "nothing", nullptr, nullptr)!=0){
      printf("Couldn't open input stream.\n");
      return -1;
    }

  //load local file:succeed!
  //    AVDictionary *options = NULL;
  //    av_dict_set(&options, "rtsp_transport", "tcp", 0);
  //    av_dict_set(&options, "max_delay", "5000000", 0);
  //    av_dict_set(&options, "stimeout", "5000000", 0);
  //    av_dict_set(&options, "buffer_size", "10240000", 0);
  //    if (avformat_open_input(&pFormatCtx, input_path, NULL, &options) != 0)
  //    {
  //        printf("Couldn't open input stream.（无法打开视频输入流）\n");
  //        return -1;
  //    }

  /* Read packets of a media file to get stream information. */
  if(avformat_find_stream_info(pFormatCtx,nullptr)<0){
      printf("Couldn't find stream information.\n");
      return -1;
    }

  videoindex = -1;
  for(i=0; i<pFormatCtx->nb_streams; i++) {
      if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
          videoindex=i;
          break;
        }
    }

  if(videoindex==-1){
      printf("Didn't find a video stream.\n");
      return -1;
    }
  //  av_dump_format(pFormatCtx, 0, input_path, 0);

  /* Find a registered decoder with a matching codec ID */
  pCodecCtx = pFormatCtx->streams[videoindex]->codec;
  pCodec    = avcodec_find_decoder(pCodecCtx->codec_id);
  if(pCodec==nullptr){
      printf("Codec not found.\n");
      return -1;
    }

  /* Initialize the AVCodecContext to use the given AVCodec */
  if(avcodec_open2(pCodecCtx, pCodec,nullptr)<0){
      printf("Could not open codec.\n");
      return -1;
    }

  pFrame    = av_frame_alloc();

  /*  Allocate and return an SwsContext. */
  /* srcW：源图像的宽
     * srcH：源图像的高
     * srcFormat：源图像的像素格式
     * dstW：目标图像的宽
     * dstH：目标图像的高
     * dstFormat：目标图像的像素格式
     * flags：设定图像拉伸使用的算法
    */
  imgrgb_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, \
                                      pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);

  packet = (AVPacket *)av_malloc(sizeof(AVPacket));
  long t0 = GetTimestampMs();
  long t1 = t0;

  AVFrame *pFrameBGR = av_frame_alloc();
  int nCVSize = av_image_get_buffer_size(AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height, 1);
  uint8_t *pCVBuf = (uint8_t *)av_malloc(nCVSize);

  if (pCVBuf) {
      av_image_fill_arrays(pFrameBGR->data
                           , pFrameBGR->linesize
                           , pCVBuf
                           , AV_PIX_FMT_BGR24
                           , pCodecCtx->width
                           , pCodecCtx->height
                           , 1);
    }

  while(av_read_frame(pFormatCtx, packet) >= 0){
      if(packet->stream_index == videoindex){
          ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
          if(ret < 0){
              printf("Decode Error.\n");
              return -1;
            }
          if(got_picture){
              //get RGB image
              try
              {
                cv::Mat image;
                image.create(cv::Size(pCodecCtx->width, pCodecCtx->height), CV_8UC3);

                if (pCVBuf) {
                    sws_scale(imgrgb_convert_ctx
                              , (const uint8_t* const*)pFrame->data
                              , pFrame->linesize
                              , 0
                              , pCodecCtx->height
                              , pFrameBGR->data
                              , pFrameBGR->linesize);
                    memcpy(image.data, pCVBuf, nCVSize);
                  }
                //                std::cout<<m_nFrameCount<<":"<<GetTimestampMs()-t0<<std::endl;
                //                t0 = GetTimestampMs();
//                if(m_nFrameCount%100==0)
//                  cv::imwrite("../result/"+std::to_string(m_nFrameCount)+"_buf.png", image);
              }
              catch (const std::exception& e)
              {
                std::cout<<e.what()<< std::endl;
              }
              m_nFrameCount++;

            }
        }
      av_packet_unref(packet);
    }

  av_free(pCVBuf);
  av_free(pFrameBGR);
  av_free(aviobuffer);
  std::cout<<"video budder decode frame:"<<m_nFrameCount<<" time consime:"<<GetTimestampMs()-t1<<std::endl;
  av_file_unmap(buf, buf_size);
  sws_freeContext(imgrgb_convert_ctx);
  //  av_free(out_buffer);
  avcodec_close(pCodecCtx);
//  avformat_close_input(&pFormatCtx);

  fclose(fp_yuv);
  fclose(fp_open);
  return 0;
}
