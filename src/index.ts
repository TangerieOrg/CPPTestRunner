#! /usr/bin/env node

import { program } from "commander";

program.parse(process.argv);

const opts = program.opts();
console.log(opts);