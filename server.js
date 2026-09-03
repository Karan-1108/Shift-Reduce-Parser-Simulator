const express = require('express');
const cors = require('cors');
const { execFile } = require('child_process');
const fs = require('fs');
const path = require('path');

const app = express();
app.use(cors());
app.use(express.json());

app.get('/', (_req, res) => {
    res.type('html').send(`<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Compiler Backend</title>
    <style>
        body { 
            margin: 0; 
            padding: 48px 24px; 
            color: #172a3a; 
            background: #f4f7f3; 
            font: 16px/1.6 "Segoe UI", sans-serif; 
        }

        main { 
            max-width: 760px; 
            margin: auto; 
            padding: 36px; 
            border: 1px solid #d9e1df; 
            border-radius: 8px; 
            background: white; 
        }

        h1 { 
            margin: 0 0 8px; 
            font: 400 38px Georgia, serif; 
        }

        .status { 
            color: #087f78; 
            font-weight: 700; 
        }

        ol { 
            padding-left: 24px; 
        }

        li { 
            margin: 10px 0; 
        }

        code { 
            padding: 3px 6px; 
            color: #087f78; 
            background: #eef6f3; 
            border-radius: 3px; 
        }

        .note { 
            margin-top: 28px; 
            padding-top: 18px; 
            border-top: 1px solid #d9e1df; 
            color: #63727a; 
        }

    </style>
</head>
<body>
    <main>
        <h1>Compiler backend</h1>
        <p class="status">● Running on http://localhost:${PORT}</p>
        <p>The backend receives an arithmetic expression and sends it through the compiler pipeline:</p>
        <ol>
            <li>
                <strong>Lexer</strong> converts source characters into tokens.
            </li>
            <li>
                <strong>SLR(1) parser</strong> performs shift and reduce operations.
            </li>
            <li>
                <strong>Symbol table</strong> records identifiers and their types.
            </li>
            <li>
                <strong>TAC generator</strong> creates three-address intermediate code.
            </li>
            <li>
                <strong>Recursive descent parser</strong> provides a performance comparison.
            </li>
        </ol>
        <p class="note">Open <code><a href="http://localhost:4200">http://localhost:4200</a></code> to use the frontend. Detailed processing logs appear in the terminal running <code>node server.js</code>.</p>
    </main>
</body>
</html>`);
});

app.get('/health', (_req, res) => {
    res.json({ status: 'ok' });
});

app.post('/api/parse', (req, res) => {
    const expr = typeof req.body?.expression === 'string'
        ? req.body.expression.trim()
        : '';

    if (!expr) {
        console.warn('[HTTP] Parse request rejected: empty expression');
        return res.status(400).json({ error: 'Please enter an arithmetic expression.' });
    }

    const startedAt = Date.now();
    console.log(`\n[HTTP] Parse request received: "${expr}"`);
    console.log('[PIPELINE] Lexer -> SLR(1) parser -> symbol table/TAC -> recursive-descent benchmark');

    const executablePaths = [
        path.join(__dirname, 'core', 'build', 'parser_core.exe'),
        path.join(__dirname, 'core', 'build', 'Release', 'parser_core.exe')
    ];
    const exePath = executablePaths.find((candidate) => fs.existsSync(candidate));

    if (!exePath) {
        console.error('[CORE] Parser executable not found');
        return res.status(503).json({
            error: 'Parser executable not found. Build the C++ core first with: cmake -S core -B core/build && cmake --build core/build'
        });
    }

    execFile(exePath, [expr], { windowsHide: true }, (error, stdout, stderr) => {
        if (error) {
            console.error('[CORE] Execution failed:', stderr || error.message);
            return res.status(500).json({ error: stderr || error.message });
        }

        if (stderr.trim()) {
            console.log(stderr.trim());
        }

        try {
            const parsedJson = JSON.parse(stdout);
            const trace = Array.isArray(parsedJson.trace) ? parsedJson.trace : [];
            const shifts = trace.filter((step) => step.action.includes('Shift')).length;
            const reductions = trace.filter((step) => step.action.includes('Reduce')).length;

            console.log('[TOKENS] Tokenization complete; see the C++ core output above');
            console.log(`[SLR] ${trace.length} parser steps (${shifts} shifts, ${reductions} reductions)`);
            trace.forEach((step) => {
                console.log(`  step ${step.step}: stack=[${step.stack}] input=[${step.buffer}] action=${step.action}`);
            });
            console.log(`[SYMBOLS] ${parsedJson.symbols?.length ?? 0} identifier(s) collected`);
            (parsedJson.symbols ?? []).forEach((symbol) => {
                console.log(`  ${symbol.name} -> ${symbol.type}, first occurrence: ${symbol.order}`);
            });
            console.log(`[TAC] ${parsedJson.tac?.length ?? 0} three-address instruction(s) generated`);
            (parsedJson.tac ?? []).forEach((instruction, index) => {
                console.log(`  t${index + 1}: ${instruction}`);
            });
            console.log(`[BENCHMARK] SLR: ${parsedJson.benchmark?.slrTimeMs} ms | RD: ${parsedJson.benchmark?.rdTimeMs} ms | RD peak stack: ${parsedJson.benchmark?.rdPeakStackDepth}`);
            console.log(`[RESULT] ${parsedJson.success ? 'Accepted' : 'Rejected'} in ${Date.now() - startedAt} ms`);
            res.json(parsedJson);
        } catch (e) {
            console.error('[CORE] Raw output was not JSON:', stdout);
            res.status(500).json({ error: "Invalid JSON received from C++ executable" });
        }
    });
});

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Backend server running on http://localhost:${PORT}`);
    console.log('');
    console.log('Compiler pipeline ready:');
    console.log('  1. Lexer             -> converts characters into tokens');
    console.log('  2. SLR(1) parser     -> performs shift/reduce parsing');
    console.log('  3. Symbol table      -> records identifiers and types');
    console.log('  4. TAC generator     -> creates intermediate three-address code');
    console.log('  5. Recursive descent  -> compares parsing time and call-stack depth');
    console.log('Waiting for an expression from the frontend...');
});