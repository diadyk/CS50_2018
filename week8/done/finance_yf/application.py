# EDITED

import os
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]
    user_info = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)[0]
    stock_info = db.execute("SELECT * FROM stocks WHERE id = :id", id=user_id)
    cash = user_info["cash"]

    if stock_info:
        total_cash = cash
        for i in stock_info:
            total_cash += lookup(i["symbol"])["price"]*i["shares"]
        return render_template("index.html",
            stock_info=stock_info, total_cash=total_cash, cash=cash, usd=usd, lookup=lookup)

    return render_template("index.html", total_cash=cash, cash=cash, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    user_id = session["user_id"]
    symbol = request.form.get("symbol")
    shares = request.form.get("shares")
    stock_info = lookup(symbol)
    user_info = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)
    if request.method == "POST":

        if not symbol:
            return apology("missing symbol", 400)

        elif not shares:
            return apology("missing shares", 400)

        elif stock_info["price"] == 0:
            return apology("invalid symbol", 400)

        full_price = stock_info["price"]*float(shares)

        if full_price <= user_info[0]["cash"]:
            stock = db.execute("SELECT * FROM stocks WHERE id = :id AND symbol = :symbol",
                        id=user_id, symbol=symbol.upper())


            new_cash = user_info[0]["cash"] - full_price
            db.execute("UPDATE users SET cash = :cash WHERE id = :id",
                       cash=new_cash,id=user_id)

            db.execute("INSERT INTO 'history' (id, symbol,shares,price) VALUES(:id, :symbol, :shares, :price)",
                id=user_id,symbol=stock_info["symbol"],shares=shares,price=stock_info["price"])

            if not stock:
                db.execute("INSERT INTO 'stocks' (id, symbol,shares,price) VALUES(:id, :symbol, :shares, :price)",
                    id=user_id, symbol=stock_info["symbol"], shares=shares, price=stock_info["price"])

            else:
                total_shares = stock[0]["shares"] + int(shares)
                price = ((stock[0]["price"] * stock[0]["shares"]) + (int(shares) * stock_info["price"])) / total_shares

                db.execute("UPDATE 'stocks' SET shares = :shares, price = :price WHERE id = :id AND symbol = :symbol",
                    shares=total_shares, price=price, id=user_id, symbol=symbol.upper())

        else:
            return apology("can't afford", 400)

        return redirect("/")


    return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    return jsonify("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    history_info = db.execute("SELECT * FROM history WHERE id = :id", id=user_id)

    if history_info:
        return render_template("history.html",history_info=history_info, usd=usd)

    return render_template("history.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        stock_info = lookup(symbol)

        if not symbol:
            return apology("missing symbol", 400)
        if stock_info["price"] == 0:
            return apology("invalid symbol", 400)

        return render_template("quoted.html",stock_info=stock_info)


    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    existing_user = db.execute("SELECT * FROM users WHERE username = :username", username=username)

    if request.method == "POST":

        if not username:
            return apology("must provide username", 400)

        elif not password:
            return apology("must provide password", 400)

        elif not confirmation or (password != confirmation):
            return apology("password don't match", 400)

        elif existing_user:
            return apology("username already taken", 400)

        hash_password = generate_password_hash(password, method='scrypt', salt_length=5)

        db.execute("INSERT INTO 'users' (username, hash) VALUES (:username, :hash_password)",
                   username=username, hash_password=hash_password)
        return redirect("/")


    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]
    user_info = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)[0]
    stock_info_user = db.execute("SELECT * FROM stocks WHERE id = :id", id=user_id)
    symbol = request.form.get('symbol')
    shares = request.form.get("shares")
    stock_info_now = lookup(symbol)

    if request.method == "POST":

        if not symbol:
            return apology("missing symbol", 400)

        elif not shares:
            return apology("missing shares", 400)

        elif stock_info_user[0]["shares"] < int(shares):
            return apology("too many shares", 403)

        full_sell_price = stock_info_now["price"]*int(shares)
        new_cash = user_info["cash"] + full_sell_price

        db.execute("UPDATE users SET cash = :cash WHERE id = :id",
                cash=new_cash,id=user_id)

        db.execute("INSERT INTO 'history' (id, symbol,shares,price) VALUES(:id, :symbol, :shares, :price)",
            id=user_id, symbol=stock_info_user[0]["symbol"], shares=-int(shares), price=stock_info_user[0]["price"])


        if int(shares) == stock_info_user[0]["shares"]:
            db.execute("DELETE FROM 'stocks' WHERE id = :id AND symbol = :symbol;",
                id=user_id, symbol=symbol)

        else:
            new_shares = stock_info_user[0]["shares"] - int(shares)
            db.execute("UPDATE 'stocks' SET shares = :shares WHERE id = :id AND symbol = :symbol",
                 id=user_id, symbol=symbol.upper(), shares=new_shares)
        return redirect("/")

    return render_template("sell.html", stock_info_user=stock_info_user)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
