# sessions
### php sessions
What is a PHP Session
 - Session variables hold information about one single user, and are available through all pages in one application.
 - ```php
   session_start()   # Starts a new session
   $_SESSION         # Stores and access session variables
   unset()           # Removes a specific session variable (e.g unset($_SESSION["favcolor"]))
   session_destroy() # Destroys all data associated with the current session
   session_unset()   # Frees all session variables
   ```

 - How does it work? How does it know it's me?
   -  When a user visits a page that calls the session_start() function, PHP checks  
for an existing session ID in the user's browser. If no session ID is found,  
PHP generates a unique, random ID.  


   -  When a user visits a page that calls the session_start() function, PHP checks  
for an existing session ID in the user's browser. If no session ID is found,  
PHP generates a unique, random ID.  


   -  On the next page load, the server gets the session ID from the cookie and uses  
it to load the session data into the PHP superglobal $_SESSION. The session  
data is then available to the current script in all scopes.  

### Problems With Sessions
 - Problem 1 — Server Memory
 - Problem 2 — Scaling
    - load balancer needs to send to same server for same user
    - or solve with session data in redis or database

# Cookies in Web 
 - small message from a web server passed to the user's browser 
 - stored in:
   - Ubuntu, browser cookies are stored in your home directory
   - Win: C:\Users[username]\AppData\Roaming[browser name]\Cookies
   - macOs:  ~/Library/Cookies