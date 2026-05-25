ADLX Python Binding Unit Tests
================================

Prerequisites:
- Python 3.13 must be installed on your system
- The ADLX Python binding wheel file (adlx-1.0.0-py313-none-win_amd64.whl) must be available

Setup and Run Tests:

1) Verify Python 3.13 is installed:
   python --version

2) Create a Python 3.13 virtual environment:
   python -m venv .venv
   
   Note: If you have multiple Python versions, specify the full path:
   C:\Path\To\Python313\python.exe -m venv .venv

3) Activate the virtual environment:
   .venv\Scripts\activate.bat

4) Install pytest:
   pip install pytest

5) Install the ADLX Python binding package:
   pip install adlx-1.0.0-py313-none-win_amd64.whl

6) Run tests using pytest:
   pytest -vs
   
   Options:
   -v : verbose output
   -s : show print statements and output

Alternative: Run Tests via VS Code
===================================

1) Complete steps 1-5 above to set up the environment

2) In VS Code, open the Testing panel (flask icon in the sidebar)

3) Configure pytest as the test framework if prompted

4) Click "Run Tests" or run individual test cases from the Testing panel

Troubleshooting:
================

- If pytest is not found, ensure the virtual environment is activated
- If the wheel installation fails, verify the file path and Python version compatibility
- For test failures, check that AMD GPU drivers are properly installed
