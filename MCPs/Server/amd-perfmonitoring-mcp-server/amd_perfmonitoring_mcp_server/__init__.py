import asyncio
import os
import sys

sys.path.append(os.path.dirname(os.path.realpath(__file__)))

from . import server


def main():
    """MCP performance monitoring Server"""
    import argparse
    import asyncio

    parser = argparse.ArgumentParser(
        description="Give a model the ability to monitor AMD performance metrics.",
    )

    args = parser.parse_args()
    asyncio.run(server.main())


# Optionally expose other important items at package level
__all__ = ["main", "server"]
