#pragma once

#include <spdlog/async.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

static void configure_logger(bool console = true,
                             std::string_view log_file_prefix = {},
                             spdlog::level::level_enum level = spdlog::level::debug) {
  std::vector<spdlog::sink_ptr> sinks{};

  if (console) {
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_st>());
  }

  if (!log_file_prefix.empty()) {
    sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink<spdlog::details::null_mutex>>(
        log_file_prefix.data(),
        0,
        0,
        false,
        3));
  }

  if (!sinks.empty()) {
    spdlog::init_thread_pool(1024, 1);

    auto logger = std::make_shared<spdlog::async_logger>("dina",
                                                         sinks.begin(),
                                                         sinks.end(),
                                                         spdlog::thread_pool(),
                                                         spdlog::async_overflow_policy::block);

    spdlog::set_default_logger(std::move(logger));
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e][%L][%n][t=%t]: %v");
    spdlog::set_level(level);
  } else {
    spdlog::set_level(spdlog::level::off);
  }
}
