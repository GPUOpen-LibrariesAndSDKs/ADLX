import asyncio
import os
import sys

sys.path.append(os.path.dirname(os.path.realpath(__file__)))

from . import server


def main():
    """MCP 3d settings Server"""
    import asyncio

    asyncio.run(server.main())


# Optionally expose other important items at package level
__all__ = ["main", "server"]
