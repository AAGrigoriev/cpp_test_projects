#include "com_parser.hpp"

#include <exception>
#include <iostream>

namespace bayan {

command_parser::command_parser(int argc, char* argv[]) : desc_("options") {
  desc_.add_options()("include,i", bpo::value<std::vector<fs::path>>(),
                      "Include path for scanning")(
      "exclude,e", bpo::value<std::vector<fs::path>>(), "Exclude directory")(
      "recursive,r", bpo::value<bool>()->default_value(false),
      "Maximum depth of scan, -1 no limit")("size,s",
                                            bpo::value<int>()->default_value(5),
                                            "Minimum file size in bytes")(
      "mask,m", bpo::value<std::vector<std::string>>(), "Masks for filename")(
      "block,b", bpo::value<int>()->default_value(10), "Block size in bytes")(
      "hash,h", bpo::value<std::string>()->default_value("crc32"),
      "Hash algorithm crc32 or crc16")("help,h", "Help screen");

  bpo::store(bpo::parse_command_line(argc, argv, desc_), mp_);

  bpo::notify(mp_);
}

std::optional<opt_data> command_parser::parse_data() {
  try {
    if (mp_.count("help")) {
      std::cout << desc_;
      return std::nullopt;
    }

    opt_data out_data;

    if (mp_.count("include")) {
      auto& elem = mp_["include"].as<std::vector<fs::path>>();

      for (auto& path : elem) {
        if (path.is_relative()) {
          std::error_code error;
          fs::path temp_path = fs::canonical(path);
          if (!error) {
            out_data.dir_opt.scan_opt.includes_path.push_back(temp_path);
          } else
            std::cerr << error.message() << " on" << path;
        } else if (fs::is_directory(path))
          out_data.dir_opt.scan_opt.includes_path.push_back(path);
      }
    } else {
      throw std::logic_error("empty include field");
    }
    if (mp_.count("exclude")) {
      auto& elem = mp_["exclude"].as<std::vector<fs::path>>();

      for (auto& path : elem) {
        if (path.is_relative()) {
          std::error_code error;
          fs::path temp_path = fs::canonical(path, error);
          if (!error) {
            out_data.dir_opt.filter_opt.exclude_path.push_back(temp_path);
          } else
            std::cerr << error.message() << " on" << path;
        } else
          out_data.dir_opt.filter_opt.exclude_path.push_back(path);
      }
    }

    if (mp_.count("recursive")) {
      out_data.dir_opt.scan_opt.recursive = mp_["recursive"].as<bool>();
    }

    if (mp_.count("size")) {
      out_data.dir_opt.filter_opt.min_file_size = mp_["size"].as<int>();
    }

    if (mp_.count("mask")) {
      out_data.dir_opt.filter_opt.mask_to_file =
          std::move(mp_["mask"].as<std::vector<std::string>>());
    }

    if (mp_.count("block")) {
      out_data.hash_opt.block_size = mp_["block"].as<int>();
    }

    if (mp_.count("hash")) {
      std::string const& str = mp_["hash"].as<std::string>();
      if (str == "crc32") {
        out_data.hash_opt.h_algo = hash_algo::crc_32;
      } else if (str == "md5") {
        out_data.hash_opt.h_algo = hash_algo::md5;
      }
    }

    return out_data;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return std::nullopt;
  }
}
}  // namespace bayan
