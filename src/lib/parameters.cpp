
#include "parameters.h"

/* we try to use gengetopt generated file in a C++ program */
/* we don't use autoconf and automake vars */

#include <iostream>
#include "stdlib.h"

#include "../../generatedsrc/cmdline.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include "../../generatedsrc/cmdline.cpp"

#pragma GCC diagnostic pop


using std::cout;
using std::endl;

Parameters::Parameters()
{
}

void Parameters::Parse(int argc, char** argv)
{
	gengetopt_args_info args_info;

	//cmdline_parser_init(&args_info);
	/* let's call our cmdline parser */
	if (cmdline_parser (argc, argv, &args_info) != 0) {
		cmdline_parser_free (&args_info); /* release allocated memory */
		exit(1);
	}

	/* initialize the parameters structure */
	struct cmdline_parser_params *params = cmdline_parser_params_create();

	if (args_info.option_file_given) {
		/*
		  override command line options,
		  but do not initialize args_info, check for required options.
		  NOTICE: we must NOT skip the 0 assignment to initialize,
		  since its default value is 1 and override defaults to 0
		  while check_required is already set to its default value, 1
		*/
		params->initialize = 0;
		params->override = 1;

		/* call the config file parser */
		if (cmdline_parser_config_file(args_info.option_file_arg, &args_info, params) != 0) {
			cmdline_parser_free (&args_info); /* release allocated memory */
			exit(1);
		}
	}

	for (unsigned i = 0 ; i < args_info.inputs_num ; ++i) {
		AddFile(args_info.inputs[i]);
	}
	for (unsigned i = 0; i != args_info.define_given; ++i) {
		AddDefine(args_info.define_arg[i]);
	}

	for (unsigned i = 0; i != args_info.include_dir_given; ++i) {
		AddInclude(args_info.include_dir_arg[i]);
	}
#if 0
	for (unsigned i = 0; i != args_info.; ++i) {
		AddExtra(args_info.[i]);
	}
#endif

	cmdline_parser_free (&args_info); /* release allocated memory */

}


