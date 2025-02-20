# EDITED

import yfinance as yf
from flask import redirect, render_template, request, session
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/1.0/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol using Yahoo Finance."""
    try:
        stock = yf.Ticker(symbol)
        info = stock.info

        price = (
            info.get("regularMarketPrice")
            or info.get("currentPrice")
            or 0.0
        )

        return {
            "name": info.get("longName", "Unknown Company"),
            "price": price,
            "symbol": info.get("symbol")
        }
    except Exception as e:
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"



