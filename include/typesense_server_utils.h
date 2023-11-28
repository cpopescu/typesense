#pragma once

#include <cmdline.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <csignal>
#include <iostream>
#include <string>

#include "collection_manager.h"
#include "http_server.h"
#include "logger.h"
#include "store.h"
#include "tsconfig.h"

extern HttpServer* server;

void catch_interrupt(int sig);

bool directory_exists(const std::string& dir_path);

void init_cmdline_options(cmdline::parser& options, int argc, char** argv);

int init_root_logger(Config& config, const std::string& server_version);

int run_server(const Config& config, const std::string& version,
               void (*master_server_routes)());
