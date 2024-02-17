import { globSync } from "glob";
import { join } from "path";
import { Action, ActionState, TestCase, TestModule } from "./types";
import { runCommand, runTest } from "./util";
import { indexOf } from "lodash";


const changeToDir : Action = ({ opts, ...state }) => {
    const originalDir = process.cwd();
    process.chdir(opts.dir);
    return {
        ...state,
        opts,
        originalDir
    }
}

const changeToOriginalDir : Action = ({ originalDir }) => { process.chdir(originalDir); }

const make = async (target : string) => { 
    await runCommand("make clean");
    await runCommand(`make ${target}`) 
}

const getTestModules : Action = async ({ executables, opts, ...state }) => {
    const modulePaths = globSync(join(process.cwd(), opts.tests, "**/*.js")).map(x => "/" + x);
    const testModules : Record<string, TestModule> = {}

    for(const p of modulePaths) {
        const m = await import(p).then(m => m.default as TestModule);
        if(executables.length === 0 || executables.includes(m.executable)) {
            if(!testModules[m.executable]) testModules[m.executable] = {
                executable: m.executable,
                cases: []
            }
        }

        testModules[m.executable].cases = [...testModules[m.executable].cases, ...m.cases]
    }

    return { ...state, executables, opts, testModules }
}


const runTests : Action = async({ executables, opts, testModules, ...state }) => {
    for(const target of opts.make) {
        console.log(`=== [${target}] ===`);
        await make(target);
        for(const module of Object.values(testModules)) {
            let passed = 0;
            for(const tcase of module.cases) {
                const result = await runTest(module.executable, tcase);
                if(result.passed) passed++;
                else { 
                    console.log(`       [${tcase.name ?? indexOf(module.cases, tcase) + 1} FAILED]`, result.output);
                }
            }
            console.log(`   ${module.executable} (${passed}/${module.cases.length})`);
        }
    }
}

export const actions : Action[] = [
    changeToDir,
    getTestModules,
    runTests
]