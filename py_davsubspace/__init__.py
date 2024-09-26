from __future__ import annotations

__submodules__ = ["hsolver"]

__all__ = list(__submodules__)

def __getattr__(attr):
    if attr == "hsolver":
        import py_davsubspace.hsolver as hsolver
        return hsolver