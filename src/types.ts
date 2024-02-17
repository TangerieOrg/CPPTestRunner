export interface TestOptions {
    make: string,
    dir: string,
    clean: boolean,
    watch: boolean,
    tests: string
}

export interface ActionState {
    executables: string[],
    opts : TestOptions,
    originalDir : string,
    testModules: Record<string, TestModule>
}

export type Action = (state : ActionState) => Promise<ActionState | void> | (ActionState | void);

export interface TestCase {
    input : string;
    expected: string;
    args?: string[];
    name?: string;
}

export interface TestModule {
    executable : string;
    cases : TestCase[];
}

export interface TestResult {
    passed : boolean;
    output : string;
}