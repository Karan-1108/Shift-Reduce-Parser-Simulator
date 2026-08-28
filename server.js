const express = require('express');
const cors = require('cors');
const { exec } = require('child_process');
const path = require('path');

const app = express();
app.use(cors());
app.use(express.json());

app.post('/api/parse', (req, res) => {
    const expr = req.body.expression || "a + b * c";
    const exePath = path.join(__dirname, 'core', 'build', 'parser_core.exe');
    
    // Pass input expression as a command-line argument to C++ binary
    exec(`"${exePath}" "${expr}"`, (error, stdout, stderr) => {
        if (error) {
            console.error("Execution error:", stderr);
            return res.status(500).json({ error: stderr || error.message });
        }
        try {
            const parsedJson = JSON.parse(stdout);
            res.json(parsedJson);
        } catch (e) {
            console.error("Raw output was not JSON:", stdout);
            res.status(500).json({ error: "Invalid JSON received from C++ executable" });
        }
    });
});

const PORT = 3000;
app.listen(PORT, () => console.log(`Backend server running on http://localhost:${PORT}`));