#pragma once
#include <sys/statvfs.h>

#include <chrono>
#include <cstdint>
#include <string>

class cached_resource_stat_t {
 private:
  const static size_t REFRESH_INTERVAL_SECS = 5;
  uint64_t disk_total_bytes = 0;
  uint64_t disk_used_bytes = 0;

  uint64_t memory_total_bytes = 0;
  uint64_t memory_available_bytes = 0;

  uint64_t swap_total_bytes = 0;
  uint64_t swap_free_bytes = 0;

  uint64_t last_checked_ts = 0;

  cached_resource_stat_t() = default;

  ~cached_resource_stat_t() = default;

 public:
  static cached_resource_stat_t& get_instance() {
    static cached_resource_stat_t instance;
    return instance;
  }

  enum resource_check_t { OK, OUT_OF_DISK, OUT_OF_MEMORY };

  // On Mac, we will only check for disk usage
  resource_check_t has_enough_resources(const std::string& data_dir_path,
                                        const int disk_used_max_percentage,
                                        const int memory_used_max_percentage);
};
