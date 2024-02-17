import { Command } from "commander";


const program = new Command();

program
    .version(process.env.npm_package_version ?? "1.0.0")
    .option("-m, --make <targets...>", "Make target to compile", [ "" ])
    .option("-d, --dir <directory>", "Directory to run in", ".")
    .option("-w, --watch", "Watch for changes and re-run", false)
    .option("-t, --tests <tests>", "Tests directory", "./tests")
    .argument("[executables...]", "Executables to run (defaults to all)", [])

export { program };