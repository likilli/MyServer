
#include "logging.h"


LogMessage::LogMessage(const char *file, int line, const char *func, int level)
    : level_(level), file_(file), line_(line), func_(func)
{
  Init(file_, line_, func_);
}

LogMessage::~LogMessage()
{
//  auto start = stream_.tellp();

  std::cout << stream_.str();
  stream_ << std::endl;
}

std::ostream& LogMessage::stream()
{
  return stream_;
}

void LogMessage::Init(const char *file, int line, const char *func)
{
  if (level_ < 1)
    return;

  stream_ << '[';

  timeval tv{};
  gettimeofday(&tv, nullptr);
  time_t t = tv.tv_sec;
  struct tm local_time{};
  localtime_r(&t, &local_time);
  struct tm *tm_time = &local_time;
  stream_ << std::setfill('0')
          << std::setw(2) << 1 + tm_time->tm_mon
          << std::setw(2) << tm_time->tm_mday
          << '/'
          << std::setw(2) << tm_time->tm_hour
          << std::setw(2) << tm_time->tm_min
          << std::setw(2) << tm_time->tm_sec
          << '.'
          << std::setw(6) << tv.tv_usec;
  std::string file_str;
  file_str.append(file);
  std::string func_str;
  func_str.append(func);
  stream_ << ":" << file_str << ":" << func_str << "(" << line << ")] ";
}