#!/bin/bash

function status {
    echo "[*] $1"
}

function positive {
    echo "[+] $1"
}

function negative {
    echo "[!] $1"
}

function exp_completed {
    positive "Experiment run completed."
    exit 0
}

function exp_failed {
    negative "Experiment run FAILED."
    exit 1
}

