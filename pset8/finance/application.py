import os, re

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded Убедитесь, что шаблоны автоматически перезагружаются
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached Убедитесь, что ответы не кэшируются
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter Пользовательский фильтр
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    list_dict = []

    table = db.execute("SELECT *, SUM(shares) FROM history WHERE id_users = ? GROUP BY symbol", session["user_id"])

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    sum_total = 0
    for row in table:
        new_dict = {}
        check_sym = lookup(row['symbol'])
        new_dict['Symbol'] = row['symbol']
        new_dict['Name'] = check_sym['name']
        new_dict['Shares'] = row['SUM(shares)']
        new_dict['Price'] = usd(check_sym['price'])
        new_dict['Total'] = usd(row['SUM(shares)'] * check_sym['price'])
        sum_total += row['SUM(shares)'] * check_sym['price']
        list_dict.append(new_dict)
    all_total = sum_total + cash[0]["cash"]

    return render_template("/index.html", list_dict=list_dict, cash=usd(cash[0]["cash"]), sum_total=usd(all_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("/buy.html")

    if request.method == "POST":
        symbol = request.form.get("buy_symbol")
        shares = float(request.form.get("shares"))
        check_name = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        if shares % 1.0 == 0:
            shares = int(shares)
        else:
            return render_template("/buy.html", error=3)

        check_symbol = lookup(symbol)
        if check_symbol == None:
            return render_template("/buy.html", error=0)
        if shares <= 0:
            return render_template("/buy.html", error=1)

        if check_name[0]["cash"] < shares * check_symbol["price"]:
            return render_template("/buy.html", error=2)
        else:
            db.execute("INSERT INTO history (id_users, symbol, shares, price, transacted) VALUES (:id_users, :symbol, :shares, :price, datetime())",
            id_users=check_name[0]["id"], symbol=check_symbol["symbol"], shares=shares, price=check_symbol["price"])
            new_cash = check_name[0]["cash"] - shares * check_symbol["price"]
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, check_name[0]["id"])
            return redirect("/")
    return apology("ATATA", 400)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    list_dict = []

    history = db.execute("SELECT * FROM history WHERE id_users = ?", session["user_id"])

    for row in history:
        new_dict = {}
        new_dict['symbol'] = row['symbol']
        new_dict['shares'] = row['shares']
        new_dict['price'] = usd(row['price'])
        new_dict['transacted'] = row['transacted']

        list_dict.append(new_dict)

    return render_template("/history.html", list_dict=list_dict)


@app.route("/personal", methods=["GET", "POST"])
@login_required
def personal():
    """Personal"""
    if request.method == "GET":
        return render_template("/personal.html")

    if request.method == "POST":

        new_pass = request.form.get("new_pass")
        check_password = request.form.get("check_new_pass")

        hash_pass_db = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])

        if not check_password_hash(hash_pass_db[0]["hash"], request.form.get("old_pass")):
            return render_template("/personal.html", error=4)

        if len(new_pass) < 8:
            return render_template("/personal.html", error=1)
        elif len(re.findall('\d', new_pass)) == 0 or len(re.findall('[^A-Za-z0-9]', new_pass)) > 0 or len(re.findall('[A-Z]', new_pass)) == 0:
            return render_template("/personal.html", error=2)
        elif new_pass != check_password:
            return render_template("/personal.html", error=3)
        else:
            new_hash_pass = generate_password_hash(new_pass)
            db.execute("UPDATE users SET hash = ? WHERE id = ?", new_hash_pass, session["user_id"])

            # Forget any user_id
            session.clear()

            # Redirect user to login form
            return redirect("/")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id Забудьте любой user_id
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
    if request.method == "GET":
        return render_template("/quote.html")

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol.isalpha() == False:
            return render_template("/quote.html", error=1)
        price = lookup(symbol)
        return render_template("/quoted.html", name=price["name"], price=price["price"], symbol=price["symbol"])
    return apology("everything is lost", 403)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        check_password = request.form.get("check_password")

        check_name_db = db.execute("SELECT * FROM users WHERE username = ?", name)

        if len(check_name_db) == 0:
            if len(password) < 8:
                return render_template("/register.html", mess=1)
            elif len(re.findall('\d', password)) == 0 or len(re.findall('[^A-Za-z0-9]', password)) > 0 or len(re.findall('[A-Z]', password)) == 0:
                return render_template("/register.html", mess=2)
            elif password != check_password:
                return render_template("/register.html", mess=3)
            else:
                hash_pass = generate_password_hash(password)
                db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash_p)", username=name, hash_p=hash_pass)
                return redirect("/")
        else:
            return render_template("/register.html", mess=0)

    return apology("everything is lost", 403)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "GET":
        check_symbol = db.execute("SELECT symbol, SUM(shares) FROM history WHERE id_users = (SELECT id FROM users WHERE id = ?) GROUP BY symbol", session["user_id"])
        symbols = []
        for a in check_symbol:
            symb = {}
            symb["symbol"] =a["symbol"]
            symb["shares"] =a["SUM(shares)"]
            symbols.append(symb)

        return render_template("/sell.html", symbols=symbols)

    if request.method == "POST":
        check_symbol = db.execute("SELECT symbol, SUM(shares) FROM history WHERE id_users = (SELECT id FROM users WHERE id = ?) GROUP BY symbol", session["user_id"])
        symbols = []
        for a in check_symbol:
            symb = {}
            symb["symbol"] =a["symbol"]
            symb["shares"] =a["SUM(shares)"]
            symbols.append(symb)
        symbol = request.form.get("symbol")
        shares = float(request.form.get("shares"))
        check_name = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        check_price = lookup(symbol)
        check_symbol2 = db.execute("SELECT symbol, SUM(shares) FROM history WHERE id_users = (SELECT id FROM users WHERE id = ?) and symbol = ?", session["user_id"], symbol)
        max_shares = check_symbol2[0]["SUM(shares)"]
        if shares % 1.0 == 0:
            shares = int(shares)
        else:
            return render_template("/sell.html", error=1, symbols=symbols)
        if shares > max_shares:
            return render_template("/sell.html", error=2, symbols=symbols)
        if shares <= 0:
            return render_template("/sell.html", error=3, symbols=symbols)

        new_cash = check_name[0]["cash"] + shares * check_price["price"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, check_name[0]["id"])
        db.execute("INSERT INTO history (id_users, symbol, shares, price, transacted) VALUES (:id_users, :symbol, :shares, :price, datetime())",
            id_users=check_name[0]["id"], symbol=check_price["symbol"], shares=-shares, price=check_price["price"])
        return redirect("/")
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
