/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 3 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef UTILS_FILESYSTEM_H_
#define UTILS_FILESYSTEM_H_

/*
 * Ubuntu 18 (gcc < 8.0.0) doesn't support plain "filesystem" include and
 * namespace. This utility simplifies the process of including "filesystem".
 */

#if __has_include(<filesystem>)

#include <filesystem>

#else

#include <experimental/filesystem>
namespace std {
namespace filesystem = experimental::filesystem;
}

#endif

#endif  // UTILS_FILESYSTEM_H_
