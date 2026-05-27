1. Generate a new SSH key
2. Add it to the SSH agent
3. Add the public key to your GitHub account
4. Use the SSH Git remote instead of HTTPS

---

## 1. Check if you already have SSH keys

Open terminal:

```bash
ls -al ~/.ssh
```

Look for files like:

```txt
id_ed25519
id_ed25519.pub
```

If they already exist, you can reuse them.

---

## 2. Generate a new SSH key

Recommended:

```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```

Example:

```bash
ssh-keygen -t ed25519 -C "sourabh@example.com"
```

You’ll see:

```txt
Enter file in which to save the key
```

Press Enter for default:

```txt
/home/youruser/.ssh/id_ed25519
```

Then:

```txt
Enter passphrase
```

* You can set one for extra security
* Or press Enter twice for no passphrase

This creates:

```txt
~/.ssh/id_ed25519
~/.ssh/id_ed25519.pub
```

---

## 3. Start SSH agent

Run:

```bash
eval "$(ssh-agent -s)"
```

You should see:

```txt
Agent pid xxxx
```

---

## 4. Add key to SSH agent

```bash
ssh-add ~/.ssh/id_ed25519
```

If successful:

```txt
Identity added
```

---

## 5. Copy the public key

Show the key:

```bash
cat ~/.ssh/id_ed25519.pub
```

Copy the entire output beginning with:

```txt
ssh-ed25519 ...
```

---

## 6. Add SSH key to GitHub

Go to:

[GitHub SSH Keys Settings](https://github.com/settings/keys?utm_source=chatgpt.com)

Click:

```txt
New SSH key
```

Fill:

* Title → your laptop name
* Key → paste the copied public key

Save.

---

## 7. Test the connection

Run:

```bash
ssh -T git@github.com
```

First time you’ll see:

```txt
Are you sure you want to continue connecting?
```

Type:

```txt
yes
```

Then you should get:

```txt
Hi username! You've successfully authenticated
```

---

## 8. Change repo remote from HTTPS to SSH

Inside your repo:

Check current remote:

```bash
git remote -v
```

If you see:

```txt
https://github.com/username/repo.git
```

change it to SSH:

```bash
git remote set-url origin git@github.com:username/repo.git
```

Verify:

```bash
git remote -v
```

Now it should show:

```txt
git@github.com:username/repo.git
```

---

## 9. Push without password

Now normal Git commands work:

```bash
git push
git pull
```

without typing GitHub username/password.

---

## Optional: Make SSH persistent after reboot

Ubuntu usually handles this automatically now, but if needed:

Create config:

```bash
nano ~/.ssh/config
```

Add:

```txt
Host github.com
  AddKeysToAgent yes
  IdentityFile ~/.ssh/id_ed25519
```

Save:

```txt
CTRL+O
ENTER
CTRL+X
```

Set permissions:

```bash
chmod 600 ~/.ssh/config
```

---

## Useful troubleshooting

### Permission denied (publickey)

Run:

```bash
ssh-add ~/.ssh/id_ed25519
```

and test again:

```bash
ssh -T git@github.com
```

---

### Wrong remote URL

Check:

```bash
git remote -v
```

SSH format must be:

```txt
git@github.com:user/repo.git
```

NOT:

```txt
https://github.com/user/repo.git
```

---

## GitHub official docs

[GitHub SSH Authentication Docs](https://docs.github.com/en/authentication/connecting-to-github-with-ssh?utm_source=chatgpt.com)
