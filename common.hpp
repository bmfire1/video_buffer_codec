#ifndef _GAMMA_OCR_COMMON_H__
#define _GAMMA_OCR_COMMON_H__

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <memory>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <sys/time.h>

#define D_OFF 0
#define D_OCR 1
#define D_KFD 2
static const int g_debug = D_OFF;

static const std::vector<std::string> g_device_list = {
  "cuda"
};


#define MAKE_PROPERTY(name, type) \
  inline const type &get_name() { return name; } \
  inline void set_name(type &&name) { name = name; } \
  inline void set_name(type &name) { name = name; }

#define DISABLE_COPY_CONSTRUCTOR(class) \
  class(class const&) = delete; \
  class &operator=(class const &) = delete;

template<typename F>
inline double TimeIt(F &&func) {
  auto start = std::chrono::steady_clock::now();
  std::forward<decltype(func)>(func)();
  auto end = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);
  return duration.count();
}

inline bool DirExist(const std::string& dirName_in){
  int ftyp = access(dirName_in.c_str(), R_OK);
  if (ftyp == 0){
      return true;
    } else{
      return false;
    }
}

inline long GetTimestampMs(){
  struct timeval t;
  gettimeofday(&t, nullptr);
  return t.tv_sec*1000 + t.tv_usec/1000;
}

#define NAMESPACE 1
#if NAMESPACE
#define BEGIN_NAMESPACE namespace vocr {
#define END_NAMESAPCE }
#define USING_NAMESAPCE using namespace vocr;
#else
#define BEGIN_NAMESPACE
#define END_NAMESAPCE
#define USING_NAMESAPCE
#endif
#endif
