import { exec, spawn } from "child_process";
import { TestCase, TestResult } from "./types";

export const runCommand = (command : string) : Promise<{ output : string, error : string, didError : boolean }> => new Promise((resolve, reject) => {
    exec(command, {encoding: "utf-8" }, (err, output, error) => {
        if(err) {
            resolve({ output, error, didError: true })
        } else {
            resolve({ output, error, didError: false })
        }
    })
})

export const runTest = (executable : string, tcase : TestCase) : Promise<TestResult> => new Promise((resolve, reject) => {
    const child = spawn(`./${executable}`, tcase.args ?? []);
    
    const state = {
        stdout: "",
        stderr: ""
    }

    child.stdout.on("data", (data : Buffer) => {
        state.stdout += data.toString();
    })

    child.stderr.on("data", (data : Buffer) => {
        state.stderr += data.toString();
    })

    child.stdin.write(tcase.input)

    child.stdin.end();

    child.on("exit", () => {
        if(state.stderr.length > 0) {
            return resolve({
                output: state.stderr.trimEnd(),
                passed: false
            })
        }


        resolve({
            output: state.stdout.trimEnd(),
            passed: state.stdout.trimEnd().endsWith(tcase.expected.trimEnd())
        })
    })
});
