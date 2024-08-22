import os

import discord

import fun
import fun2

intents = discord.Intents.default()
intents.message_content = True
client = discord.Client(intents=intents)

# ban = {1233490281861615778}
ban = {}

@client.event
async def on_ready():
    print(f"\n\nLogged in as {client.user.name}")
    print("Bot is ready!\n\n")
    fun2.build()


@client.event
async def on_message(text):
    if text.author == client.user:
        return

    # LIST OF COMMANDS
    if text.content.lower() == "help me prime":
        if text.author.id in ban:
            await text.reply("# Nigga you are banned :speaking_head:")
            return
        await fun.help(text)

    # CALCULATE
    elif text.content.lower()[:6] == ".calc ":
        if text.author.id in ban:
            await text.reply("# Nigga you are banned :speaking_head:")
            return
        await fun.calc(text)

    # LIST OF PLAYERS PLAYING
    elif text.content.lower()[:5] == ".list":
        if text.author.id in ban:
            await text.reply("# Nigga you are banned :speaking_head:")
            return
        await fun.list(text)

    # PLAY SOLO
    elif text.content.lower()[:5] == ".solo":
        if text.author.id in ban:
            await text.reply("# Nigga you are banned :speaking_head:")
            return
        await fun.solo(text)

    # CHALLENGE OPPONENT
    elif text.content.lower()[:8] == ".battle ":
        if text.author.id in ban:
            await text.reply("# Nigga you are banned :speaking_head:")
            return
        await fun.challenge(text)

    # CANCEL CHALLENGE
    elif text.content.lower()[:7] == ".cancel":
        if text.author.id in ban:
            await text.reply("# Nigga you are banned :speaking_head:")
            return
        await fun.cancel(text, client)

    # REJECT CHALLENGE
    elif text.content.lower()[:3] == ".no":
        if text.author.id in ban:
            await text.reply("# Nigga you are banned :speaking_head:")
            return
        await fun.no(text)

    # ACCEPT CHALLENGE
    elif text.content.lower()[:4] == ".yes":
        if text.author.id in ban:
            await text.reply("# Nigga you are banned :speaking_head:")
            return
        await fun.yes(text, client)

    # SUBMIT YOUR NUMBER
    elif text.content.lower()[:6] == ".code ":
        if text.author.id in ban:
            await text.reply("# Nigga you are banned :speaking_head:")
            return
        await fun.code(text)

    # GUESS OPPONENT'S NUMBER
    elif text.content.lower()[:7] == ".guess ":
        if text.author.id in ban:
            await text.reply("# Nigga you are banned :speaking_head:")
            return
        await fun.guess(text)

    # RESIGN
    elif text.content.lower()[:7] == ".resign":
        if text.author.id in ban:
            await text.reply("# Nigga you are banned :speaking_head:")
            return
        await fun.resign(text)

    # OFFER DRAW
    elif text.content.lower()[:5] == ".draw":
        if text.author.id in ban:
            await text.reply("# Nigga you are banned :speaking_head:")
            return
        await fun.offerDraw(text)

    # CHECK PREVIOUS MOVES
    elif text.content.lower()[:12] == ".check moves":
        if text.author.id in ban:
            await text.reply("# Nigga you are banned :speaking_head:")
            return
        await fun.checkMoves(text, client)


my_secret = '*************************************************************'
client.run(my_secret)
