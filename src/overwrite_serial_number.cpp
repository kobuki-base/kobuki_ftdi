/*
 * License: BSD
 * URL: https://raw.githubusercontent.com/kobuki-base/kobuki_ftdi/license/LICENSE
*/
/**
 * @file src/overwrite_serial_number.cpp
 * @brief Overwrite serial number of ftdi device.
 *
 * <b>License:</b> BSD https://raw.github.com/yujinrobot/kobuki_core/hydro-devel/kobuki_ftdi/LICENSE
 **/

/*****************************************************************************
 ** Includes
 *****************************************************************************/

#include <iostream>
#include <ecl/command_line.hpp>
#include "kobuki_ftdi/writer.hpp"
#include "kobuki_ftdi/scanner.hpp"

/*****************************************************************************
 ** Using
 *****************************************************************************/

using ecl::CmdLine;
using ecl::UnlabeledValueArg;
using ecl::ValueArg;
using ecl::SwitchArg;
using std::string;

/*****************************************************************************
 ** Main
 *****************************************************************************/

int main(int argc, char **argv)
{
  /*********************
   ** Parse Command Line
   **********************/
  CmdLine cmd_line("This is used to write a new serial id string to the ftdi device.", ' ', "0.1");
  ValueArg<std::string> old_arg(
      "o", "old", "Identify the device via the old serial id (if there are multiple devices attached) ['unspecified'].", false,
      "unspecified", "string");
  UnlabeledValueArg<std::string> new_arg("new_id", "New serial id used to identify the device [xxx].", true,
                                         "xxx", "string");
  cmd_line.add(old_arg);
  cmd_line.add(new_arg);
  cmd_line.parse(argc, argv);
  bool using_old_id = false;
  string old_id;
  if (old_arg.getValue() != "unspecified")
  {
    using_old_id = true;
    old_id = old_arg.getValue();
  }
  string new_id = new_arg.getValue();


  /*********************
   ** Debug output
   **********************/
  std::cout << "Input Information" << std::endl;
  if (!using_old_id)
  {
    std::cout << "  Old id: unused (first device found.)" << std::endl;
  }
  else
  {
    std::cout << "  Old id: " << old_id << std::endl;
  }
  std::cout << "  New id: " << new_id << std::endl;


  /*********************
   ** Writing serial id
   **********************/
  FTDI_Writer writer;
  int ret_val = 0;
  ret_val = writer.write(new_id);
  if (ret_val<0) {
    std::cerr << "Something went wrong." << std::endl;
    return ret_val;
  }

  FTDI_Scanner scanner;
  ret_val = scanner.reset();
  if (ret_val<0 && ret_val !=-19) {
    std::cerr << "Something went wrong." << std::endl;
    return ret_val;
  }

  std::cout << "ret_val: " << ret_val << std::endl;
  return 0;
}

