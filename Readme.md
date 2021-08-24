## **Decode video buffer**  

使用ffmpeg对视频文件进行解码的例子网上比较多.但是在实际的工程应用中,为了io效率更高,解码模块不会先将收到的视频内容保存为本地文件再进行解码.
所以使用直接对**视频内存**进行解码很有必要,但是网上能找打的例子,以及ffmpeg的sample并不能直接适配.

#### buffer解码主要流程

设置一个小的buf, 解码过程不断的copy 大的videobuffer到小的buf.
aviobuffer=(unsigne
d char *)av_malloc(buffer_size);

#### 关键点

###### readbuffer回调函数

从输入的视频buffer中每次读取buf_size大小到buf中

###### seek回调函数

花费了一些时间去研究

通过offset和whence去读取制定位置的视频buffer,whence的取值如下:

```cpp
/**
 * ORing this as the "whence" parameter to a seek function causes it to
 * return the filesize without seeking anywhere. Supporting this is optional.
 * If it is not supported then the seek function will return <0.
 */
#define AVSEEK_SIZE 0x10000

/**
 * Passing this flag as the "whence" parameter to a seek function causes it to
 * seek by any means (like reopening and linear reading) or other normally unreasonable
 * means that can be extremely slow.
 * This may be ignored by the seek code.
 */
#define AVSEEK_FORCE 0x20000

# define SEEK_SET	0	/* Seek from beginning of file.  */
# define SEEK_CUR	1	/* Seek from current position.  */
# define SEEK_END	2	/* Seek from end of file.  */
```

###### 自定义video_buf

```

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
```



#### 编译

###### 依赖

ffmpeg三方库

opencv(可选, 用于保存视频帧)

###### 编译

mkdir build && cd build && cmake .. &&make





