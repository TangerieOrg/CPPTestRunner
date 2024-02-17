#! /usr/bin/env node

import { actions } from "./actions";
import { program } from "./options";
import { ActionState, TestOptions } from "./types";
import { runCommand, runTest } from "./util";

program.action(async (executables : string[], opts : TestOptions) => {
    let state : ActionState = {
        originalDir: "",
        executables,
        opts,
        testModules: {}
    }

    for(const a of actions) { 
        const next = await (a(state));
        if(next != undefined) state = next
    }

    executables = state.executables;
    opts = state.opts;
})
// -d example -t tests -m asan msan
program.parse();