# -------------------------------------------------------------------------
# Copyright (c) 2024-2025 Advanced Micro Devices, Inc. All rights reserved.
# -------------------------------------------------------------------------

import logging
import logging.handlers
import os

import sys
import threading
from termcolor import colored

# default to no log, no print for production
enable_log = False
chat_logger = None
log_mutex = threading.Lock()


def init_log_configuration():
    global enable_log, chat_logger

    # Handle PyInstaller bundled executable
    if getattr(sys, 'frozen', False):
        # If the application is run as a bundle, the PyInstaller bootloader
        # extends the sys module by a flag frozen=True and sets the app 
        # path into variable _MEIPASS.
        application_path = os.path.dirname(sys.executable)
    else:
        application_path = os.path.dirname(__file__)

    CHAT_LOGGING_FOLDER = os.path.join(application_path, "logs")
    if os.path.exists(CHAT_LOGGING_FOLDER) is False:
        os.makedirs(CHAT_LOGGING_FOLDER)

    logging.basicConfig(
        filename=os.path.join(CHAT_LOGGING_FOLDER, "simple_chatbot_mcp_client.log"),
        encoding="utf-8",
        level=logging.DEBUG,
        format="%(asctime)s %(levelname)-8s [%(name)s] %(message)s",
        # format="%(levelname)s|%(asctime)s|%(name)s %(message)s",
    )
    chat_logger = logging.getLogger("adlx_mcp_client")
    enable_log = True


def log_with_color(text: str, color: str = "black"):
    global enable_log, chat_logger
    if not enable_log:
        return

    with log_mutex:
        log_lines = text.split("\n")

        for line in log_lines:
            try:
                encoded = line.encode("utf-8", errors="ignore").decode("utf-8")
                chat_logger.info(encoded)
                print(colored(encoded, color))
            except Exception as e:
                print(e)