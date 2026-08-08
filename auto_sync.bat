@echo off
cd /d "%~dp0"
git add .
git commit -m "Auto-sync update: %date% %time%"
git push origin main