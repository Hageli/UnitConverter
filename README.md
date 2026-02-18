<h1>Unit Converter </h1>
This program contains type conversion for the most popular <strong>Weight, Size, Volume, Temperature, and Currency</strong> units.

This program has a simple menu structure that can be run in the terminal.

<strong>Some libraries are needed to run this program:</strong>
On linux, run the following commands to use this program:

1. sudo apt install libcurl4-openssl-dev

2. sudo apt install libjson-c-dev

3. gcc -o unit ./unitConverter.c -lcurl -ljson-c

And to run the program:

4. ./unit

<h2>Currency rate relevancy</h2>

This programs fetches exchange rates for the currencies from the Bank of Finland's open data API. This ensures relevancy of the exchange rate information and provides the users with close to real-time exchange rate data. 
Currently supported currencies are CNY, SEK, USD, JPY, and GBP with Euro being the only input currency. 
