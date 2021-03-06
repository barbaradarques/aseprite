// Aseprite Base Library
// Copyright (c) 2001-2013 David Capello
//
// This source file is distributed under MIT license,
// please read LICENSE.txt for more information.

#ifndef BASE_LAUNCHER_H_INCLUDED
#define BASE_LAUNCHER_H_INCLUDED

#include <string>

namespace base {
  namespace launcher {

    bool open_url(const std::string& url);
    bool open_file(const std::string& file);
    bool open_folder(const std::string& file);

    bool support_open_folder();

  } // namespace launcher
} // namespace base

#endif
