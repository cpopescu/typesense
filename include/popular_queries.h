#pragma once

#include <tsl/htrie_map.h>

#include <atomic>
#include <json.hpp>
#include <shared_mutex>
#include <string>
#include <vector>

class PopularQueries {
 public:
  struct QWithTimestamp {
    std::string query;
    uint64_t timestamp;

    QWithTimestamp(const std::string& query, uint64_t timestamp)
        : query(query), timestamp(timestamp) {}
  };

  static const size_t QUERY_FINALIZATION_INTERVAL_MICROS = 4 * 1000 * 1000;

 private:
  size_t k;
  const size_t max_size;

  // counts aggregated within the current node
  tsl::htrie_map<char, uint32_t> local_counts;
  std::shared_mutex lmutex;

  std::unordered_map<std::string, std::vector<QWithTimestamp>>
      user_prefix_queries;
  std::shared_mutex umutex;

 public:
  PopularQueries(size_t k);

  void add(const std::string& value, const bool live_query,
           const std::string& user_id, uint64_t now_ts_us = 0);

  void compact_user_queries(uint64_t now_ts_us);

  void serialize_as_docs(std::string& docs);

  void reset_local_counts();

  size_t get_k();

  std::unordered_map<std::string, std::vector<QWithTimestamp>>
  get_user_prefix_queries();

  tsl::htrie_map<char, uint32_t> get_local_counts();
};
