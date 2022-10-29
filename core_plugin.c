#include <rz_analysis.h>
#include <rz_cmd.h>
#include <rz_cons.h>
#include <rz_core.h>
#include <rz_il.h>
#include <rz_lib.h>
#include <rz_types.h>
#include <stdlib.h>
#include <string.h>

static const RzCmdDescArg plug_args = {
    0,
};
static const RzCmdDescHelp plug_help = {
    .summary = "Help of the example core plugin",
    .args = &plug_args,
};

static const RzCmdDescHelp plug_usage = {
    .summary = "Command of the example core plugin",
    .args = &plug_args,
};

static char *my_core_function(RzCore *core) {
  eprintf("my_core_function is executed!\n");
}

/*
  This func will start every time when user prints 'plug' in CLI
*/
static RzCmdStatus plug_handler(RzCore *core, int argc, const char **argv) {
  eprintf("Command is handled!\n");
  my_core_function(core);
  return RZ_CMD_STATUS_OK;
}

/*
  This func is called when plugin unloads, e.g. when rizin exit
*/
static bool rz_cmd_plug_fini(RzCore *core) {
  eprintf("I'm finished!\n");
  return true;
}

/*
  Here we do init stuff and setup commands and args
*/
static bool rz_cmd_plug_init(RzCore *core) {
  RzCmd *rcmd = core->rcmd;
  RzConfig *cfg = core->config;
  RzCmdDesc *root_cd = rz_cmd_get_root(rcmd);
  eprintf("I'm inited!\n");
  if (!root_cd) {
    rz_warn_if_reached();
    return false;
  }

  RzCmdDesc *plug = rz_cmd_desc_group_new(rcmd, root_cd, "plug", plug_handler,
                                          &plug_help, &plug_usage);

  if (!plug) {
    rz_warn_if_reached();
    return false;
  }

  rz_warn_if_fail(
      rz_cmd_desc_argv_new(rcmd, root_cd, "plug", plug_handler, &plug_help));

  return true;
}

RzCorePlugin rz_core_plugin_example = {
    .name = "rz-core-plugin",
    .author = "ogre2007",
    .desc = "Example plugin for Rizin reverse engineering framework",
    .license = "GNU GPLv3",
    .init = rz_cmd_plug_init,
    .fini = rz_cmd_plug_fini};

RZ_API RzLibStruct rizin_plugin = {.type = RZ_LIB_TYPE_CORE,
                                   .data = &rz_core_plugin_example,
                                   .version = RZ_VERSION,
                                   .pkgname = "rz-core-plugin"};
