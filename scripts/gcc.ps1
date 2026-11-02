<#
.SYNOPSIS
    Locate gcc and compile a source file. Called by .vscode/tasks.json.

.DESCRIPTION
    Searches for a compiler in this order, uses the first one found:
      1. -Compiler argument (explicit path)
      2. %MINGW_HOME%\bin\gcc.exe
      3. gcc on PATH
      4. Common Windows install locations

    Build flags are fixed at -g -Wall -Wextra -std=c17, matching the
    acceptance criteria in README.md (zero warnings).

    NOTE: this file is intentionally ASCII-only. Windows PowerShell 5.1
    reads BOM-less files as ANSI and mangles non-ASCII string literals.

.PARAMETER Source
    The .c file to compile (tasks.json passes ${file}).

.PARAMETER Output
    Output path (tasks.json passes ${workspaceFolder}/bin/<name>.exe).

.PARAMETER Asm
    Switch to assembly mode: -S -O2 -masm=intel.

.EXAMPLE
    powershell -File scripts/gcc.ps1 -Source c-basics/bit01.c -Output bin/bit01.exe

.EXAMPLE
    powershell -File scripts/gcc.ps1 -Source c-basics/volatile-nv.c -Output bin/volatile-nv.s -Asm
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$Source,

    [Parameter(Mandatory = $true)]
    [string]$Output,

    [switch]$Asm,

    [string]$Compiler
)

$ErrorActionPreference = 'Stop'

function Resolve-Gcc {
    param([string]$Explicit)

    # 1. explicit path
    if ($Explicit) {
        if (Test-Path $Explicit) { return (Resolve-Path $Explicit).Path }
        throw "Compiler not found: $Explicit"
    }

    # 2. MINGW_HOME
    if ($env:MINGW_HOME) {
        $candidate = Join-Path $env:MINGW_HOME 'bin\gcc.exe'
        if (Test-Path $candidate) { return $candidate }
    }

    # 3. PATH
    $onPath = Get-Command gcc -ErrorAction SilentlyContinue
    if ($onPath) { return $onPath.Source }

    # 4. common install locations
    $common = @(
        'C:\mingw64\bin\gcc.exe',
        'C:\msys64\mingw64\bin\gcc.exe',
        'C:\Program Files\mingw-w64\mingw64\bin\gcc.exe',
        'D:\Software\mingw64\mingw64\bin\gcc.exe'
    )
    foreach ($p in $common) {
        if (Test-Path $p) { return $p }
    }

    throw @"
gcc not found. Fix it in one of these ways:

  1. Add the MinGW bin directory to PATH
  2. Set MINGW_HOME to the MinGW root (must contain bin\gcc.exe)
  3. Pass -Compiler <full path to gcc.exe> in tasks.json
"@
}

$gcc = Resolve-Gcc -Explicit $Compiler

# create output directory if missing
$outDir = Split-Path -Parent $Output
if ($outDir -and -not (Test-Path $outDir)) {
    New-Item -ItemType Directory -Force -Path $outDir | Out-Null
}

$flags = if ($Asm) {
    @('-S', '-O2', '-masm=intel')
} else {
    @('-g', '-Wall', '-Wextra', '-std=c17')
}

Write-Host "gcc   : $gcc" -ForegroundColor DarkGray
Write-Host "source: $Source" -ForegroundColor DarkGray
Write-Host "output: $Output" -ForegroundColor DarkGray

& $gcc @flags $Source -o $Output
$code = $LASTEXITCODE

if ($code -ne 0) {
    Write-Host "BUILD FAILED (exit $code)" -ForegroundColor Red
} else {
    Write-Host "BUILD OK" -ForegroundColor Green
}

exit $code
