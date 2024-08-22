import random

import fun2


# GLOBAL VARIABLES
class UserGame:
    round = 1
    opp = num = userTurn = pastMoves = draw = None


mpp = {}
calcPerm = {852956674763391047, 291974450348294155, 1241925183078666290}
# Prime, Eardrum, and Ryuu


def repeating(num):
    st = {}
    for i in range(len(num)):
        if num[i] in st:
            return True
        st[num[i]] = 1
    return False


def calc2(a):
    dp = [[0] * 60 for _ in range(20)]
    nums = [[] for _ in range(60)]
    res = "```c\nStarting:   "
    for i in a:
        res += f"{i} "
    res += "\n"
    a.sort()
    res += "Sorted:     "
    for i in a:
        res += f"{i} "
    res += "\n"
    res += f"Count:      {len(a)}\nSum:        {sum(a)}\n\n"
    for i in range(len(a)):
        dp[i][0] = 1
        for target in range(1, 60):
            if dp[i][target]:
                dp[i + 1][target] = 1
            elif target - a[i] >= 0 and not nums[target] and dp[i][target - a[i]]:
                dp[i + 1][target] = 1
                nums[target] = nums[target - a[i]] + [a[i]]
    for i in range(23, 28):
        res += f"{i} = "
        if nums[i]:
            res += f"{nums[i]}\n"
        else:
            res += "IMPOSSIBLE\n"
    res += "```"
    return res


#################################################################################################################


async def work(text, client):
    user = await client.fetch_user(text.author.id)
    await user.send("Hello!")


#################################################################################################################


async def winner(text, ID):
    m = ":tada: " + f"<@{ID}>" + " won the game! Congratulations! :tada:"
    await text.channel.send(m)
    m = "# Unravel Match Summary\n**Match Status: " + f"<@{ID}> Won :tada:**\n\n" + f"<@{ID}>'s Number: ||{mpp[mpp[ID].opp].num}||\n" + f"<@{mpp[ID].opp}>'s Number: ||{mpp[ID].num}||"
    await text.channel.send(m)
    if ID in mpp and mpp[ID].opp in mpp:
        del mpp[mpp[ID].opp]
    if ID in mpp:
        del mpp[ID]
    print(f"Game between {text.author.name} and {user.name} ended!")


#################################################################################################################


async def drawn(text, agree):
    m = "Both players agreed to draw the game!" if agree else ":tada: Both players guessed correctly! It's a draw! :tada:"
    await text.channel.send(m)
    await text.channel.send(f"# Unravel Match Summary\nMatch Status: **Draw**\n\n<@{mpp[text.author.id].opp}>'s Number: **{mpp[text.author.id].num}**\n<@{mpp[mpp[text.author.id].opp].opp}>'s Number: **{mpp[mpp[text.author.id].opp].num}**")
    del mpp[mpp[text.author.id].opp]
    del mpp[text.author.id]
    print(f"Game between {text.author.name} and {user.name} ended!")
    return


#################################################################################################################


async def calc(text):
    if len(text.content) == 6:
        return
    txt = text.content.lower()[6:]
    if any(txt[i] != " " and "0" > txt[i] > "9" for i in range(len(txt))):
        await text.reply("Please enter the cards only after **.calc**")
        return
    if text.author.id not in calcPerm:
        await text.reply(
            "Sorry bro, Prime sensei haven't given you permission to use it xD"
        )
        return
    ls = [int(x) for x in txt.split()]
    m = calc2(ls)
    await text.reply(m)


#################################################################################################################


async def help(text):
    await text.reply("**Master Prime is a busy person, if you want help ask me,\nHere are the list of commands:**\n```c\n1. Send challenge              .battle @user\n   Withdraw challenge          .cancel\n   Forfeit game                .resign\n   Offer Draw                  .draw\n2. Select number               .code XXXX\n3. Guess opponent's number     .guess XXXX\n4. Check previous guesses      .check moves OR .check moves @user\n5. Play solo game              .solo\n```")


#################################################################################################################


async def list(text):
    if len(mpp) == 0:
        await text.reply("Noone is playing right now!")
        return
    i = 1
    m = "**List of players who're playing:**\n"
    for ID in mpp:
        m += f"{i}. <@{ID}>\n"
        i += 1
    await text.reply(m)


#################################################################################################################


async def challenge(text):
    if len(text.mentions) == 0:
        await text.reply("Please mention a valid user to challenge!")
        return
    if text.mentions[0].id == text.author.id:
        await text.reply("You can't challenge yourself dummy!")
        return
    if text.mentions[0].id in mpp:
        await text.reply("Your opponent is a little busy, Please wait!")
        return
    if text.author.id in mpp:
        await text.reply("You are already in a game, Please wait!")
        return
    await text.reply(
        f"<@{text.mentions[0].id}>" +
        f" would you like to play Unravel with <@{text.author.id}>" +
        "?\nRespond with **.yes**/**.no**")

    mpp[text.author.id] = UserGame()
    mpp[text.author.id].num = text.channel
    mpp[text.author.id].opp = text.mentions[0].id
    mpp[text.author.id].userTurn = -10
    mpp[text.author.id].pastMoves = []

    mpp[text.mentions[0].id] = UserGame()
    mpp[text.mentions[0].id].num = text.channel
    mpp[text.mentions[0].id].opp = text.author.id
    mpp[text.mentions[0].id].userTurn = 10
    mpp[text.mentions[0].id].pastMoves = []


#################################################################################################################


async def solo(text):
    if text.author.id in mpp:
        await text.reply("You are already in a game, finish that first!")
        return
    await text.reply("I'm ready to play solo! Guess a 4-digit number with no repeating digits.")

    hard = len(text.content) >= 10 and text.content.lower()[:10] == ".solo hard"
    if not hard:
        hard = random.randint(1, 5) == 3
    if not hard and (text.author.id == 1233490281861615778 or text.author.id == 595130397063380992):
        hard = random.randint(1, 10) > 5
    n = str(random.randint(123, 10000))
    n = "0" + n if len(n) < 4 else n
    while repeating(n):
        n = str(random.randint(123, 10000))
        n = "0" + n if len(n) < 4 else n
    mpp[text.author.id] = UserGame()
    mpp[text.author.id].num = "XXXX" if hard else n
    mpp[text.author.id].opp = text.author.id
    mpp[text.author.id].userTurn = 1
    mpp[text.author.id].pastMoves = []


#################################################################################################################


async def cancel(text, client):
    print(len(mpp))
    if text.author.id not in mpp:
        await text.reply("You haven't sent any challenge yet!")
        return
    if mpp[text.author.id].userTurn != -10:
        await text.reply("You are already inside a game!")
        return
    opponent = await client.fetch_user(mpp[text.author.id].opp)
    await text.reply(
        f"Your challenge against **{opponent.name}** has been cancelled!")
    del mpp[mpp[text.author.id].opp]
    del mpp[text.author.id]


#################################################################################################################


async def yes(text, client):
    if text.author.id not in mpp:
        await text.reply("No one challenged you bruh :upside_down:")
        return
    if mpp[text.author.id].userTurn != 10:
        await text.reply("Have some patience bruh :upside_down:")
        return
    m = "A game between " + f"<@{mpp[text.author.id].opp}>" + " and " + f"<@{text.author.id}>" + " has started!\nBoth players dm me your codes!"
    await text.channel.send(m)
    mpp[text.author.id].userTurn = mpp[mpp[text.author.id].opp].userTurn = -1

    m = "You are playing a game against "
    m2 = "Submit your code here using: **.code XXXX**"
    user = await client.fetch_user(text.author.id)
    await user.send(m + f"<@{mpp[text.author.id].opp}>.\n" + m2)
    user = await client.fetch_user(mpp[text.author.id].opp)
    await user.send(m + f"<@{text.author.id}>.\n" + m2)
    print(f"{text.author.name} and {user.name} started a game")


#################################################################################################################


async def no(text):
    if text.author.id not in mpp:
        await text.reply("No one challenged you bruh :upside_down:")
        return
    if mpp[text.author.id].userTurn != 10:
        await text.reply("Have some patience bruh :upside_down:")
        return
    m = f"<@{mpp[text.author.id].opp}>" + " your challenge has been declined by "
    m += f"<@{text.author.id}>"
    # print(mpp)
    await text.channel.send(m)
    del mpp[mpp[text.author.id].opp]
    del mpp[text.author.id]


#################################################################################################################


async def code(text):
    if text.author.id not in mpp or abs(mpp[text.author.id].userTurn) == 10:
        await text.reply("You you currently not in any game right now!")
        return
    if (mpp[text.author.id].userTurn - 1) / 2 == 0:
        await text.reply("You have already sent your code! Can't change now!")
        return
    isNum = 1
    for c in text.content[6:10]:
        if c > '9' or c < '0':
            isNum = 0
            break
    if len(text.content[5:]) != 5 or not isNum or repeating(
            text.content[6:10]):
        await text.reply("Invalid code, please try again.")
        return
    if mpp[mpp[text.author.id].opp].userTurn == 0:
        m = "Both players have send their codes. Now start guessing!"
        m += " (Use **.guess XXXX**)\n" + f"<@{text.author.id}>"
        m += " it's your turn to move :speaking_head:"
        await mpp[mpp[text.author.id].opp].num.send(m)
        mpp[text.author.id].userTurn = 1
    else:
        mpp[text.author.id].userTurn = 0
        m = f"<@{text.author.id}> has send their code."
        await mpp[text.author.id].num.send(m)
    mpp[mpp[text.author.id].opp].num = text.content[6:10]
    await text.reply("Your code has been taken!")


#################################################################################################################


async def guess(text):
    if len(text.content) < 11:
        await text.reply("Invalid code, please try again.")
        return
    if text.author.id not in mpp:
        await text.reply("You are not playing any game currently")
        return
    num = True
    for c in text.content[7:11]:
        if c > '9' or c < '0':
            num = False
            break
    if len(text.content) < 5 or not num or repeating(text.content[7:11]):
        await text.reply("Please enter a valid guess")
        return
    if mpp[text.author.id].userTurn != 1:
        await text.reply("Wait bro it's not your turn yet!")
        return

    a, b = text.content[7:11], mpp[text.author.id].num
    # print(mpp[text.author.id].num)
    if mpp[text.author.id].num == "XXXX":
        p = fun2.guess(text, a)
        d, f = p[0], p[1]
        mpp[text.author.id].pastMoves.append([a, d, f])
        await text.reply(f"**Round {mpp[text.author.id].round}**\n**Guess: {a}**\n**Dots: "+ f"{d} | Fames: {f}**")
        mpp[text.author.id].round += 1
        if f == 4:
            await text.reply(f":tada: Congratulations! You guessed it in **{mpp[text.author.id].round-1} attempts**! :tada:")
            fun2.getRand(text)
            del mpp[text.author.id]
        elif mpp[text.author.id].round >= 16:
            await text.reply(
                f"Sorry, you ran out of attempts. The secret number was ||{fun2.getRand()}||."
            )
            del mpp[text.author.id]
        return

    d = f = 0
    for i in range(4):
        if a[i] == b[i]:
            f += 1
            d -= 1
        if a[i] in b:
            d += 1
    solo = mpp[text.author.id].opp == text.author.id
    mpp[text.author.id].pastMoves.append([a, d, f])
    if not solo:
        if mpp[mpp[text.author.id].opp].draw is True:
            mpp[mpp[text.author.id].opp].draw = False
        await text.reply(f"**Round {mpp[text.author.id].round}**\n**<@{text.author.id}>'s guess:{a}**\n**Dots: " + f"{d} | Fames: {f}**")
    else:
        await text.reply(f"**Round {mpp[text.author.id].round}**\n**Guess: {a}**\n**Dots: " + f"{d} | Fames: {f}**")
        mpp[text.author.id].round += 1
        if f == 4:
            await text.reply(f":tada: Congratulations! You guessed it in **{mpp[text.author.id].round-1} attempts**! :tada:")
            del mpp[text.author.id]
        elif mpp[text.author.id].round >= 16:
            await text.reply(f"Sorry, you ran out of attempts. The secret number was ||{mpp[text.author.id].num}||.")
            del mpp[text.author.id]
        return

    # Game ends if all 4 digits are correct
    if f == 4:
        mpp[text.author.id].userTurn = -1
    if f != 4 and mpp[mpp[text.author.id].opp].userTurn == -1:
        await winner(text, mpp[text.author.id].opp)
        return
    if (f == 4
            and mpp[text.author.id].round < mpp[mpp[text.author.id].opp].round
        ) and mpp[mpp[text.author.id].opp].userTurn != -1:
        await winner(text, text.author.id)
        return

    elif f == 4 and mpp[mpp[text.author.id].opp].userTurn == -1:
        await drawn(text, False)

    m = f"<@{mpp[text.author.id].opp}>" + " it's your turn to guess!"
    await text.channel.send(m)
    mpp[text.author.id].userTurn = 0
    mpp[mpp[text.author.id].opp].userTurn = 1
    mpp[text.author.id].round += 1
    if f == 4:
        mpp[text.author.id].userTurn = -1


#################################################################################################################


async def checkMoves(text, client):
    if text.author.id not in mpp and len(text.mentions) == 0:
        await text.reply("You are not playing any game currently")
        return
    if len(text.mentions) and text.mentions[0].id not in mpp:
        await text.reply("The person is not playing any game right now!")
        return
    u1 = u2 = None
    if len(text.mentions) == 0:
        u1, u2 = mpp[text.author.id], mpp[mpp[text.author.id].opp]
    else:
        u1, u2 = mpp[text.mentions[0].id], mpp[mpp[text.mentions[0].id].opp]
    user = await client.fetch_user(u2.opp)
    name1 = "Prime Sensei" if user.name == "prime7810" else user.name
    user = await client.fetch_user(u1.opp)
    name2 = "Prime Sensei" if user.name == "prime7810" else user.name
    m = ""
    solo = text.author.id == mpp[text.author.id].opp if len(
        text.mentions) == 0 else text.mentions[0].id == mpp[
            text.mentions[0].id].opp
    if not solo:
        m = f"**Game between {name1} and {name2}:**\n```c\n{name1}'s moves:\n"
    else:
        m = f"**SOLO GAME:**\n```c\n{name1}'s moves:\n"
    cnt = 1
    for i in u1.pastMoves:
        m += f"{cnt}. {i[0]} "
        if not i[1] and not i[2]:
            m += "none\n"
            cnt += 1
            continue
        if i[1]:
            m += f"{i[1]}d "
        if i[2]:
            m += f"{i[2]}f"
        m += "\n"
        cnt += 1
    if solo:
        m += "```"
        await text.reply(m)
        return
    m += f"\n{name2}'s moves:\n"
    cnt = 1
    for i in u2.pastMoves:
        m += f"{cnt}. {i[0]} "
        if not i[1] and not i[2]:
            m += "none\n"
            cnt += 1
            continue
        if i[1]:
            m += f"{i[1]}d "
        if i[2]:
            m += f"{i[2]}f"
        m += "\n"
        cnt += 1
    m += "```"
    await text.reply(m)


#################################################################################################################


async def resign(text):
    if text.author.id not in mpp:
        await text.reply("You are not playing any game currently")
        return
    if mpp[text.author.id].opp == text.author.id:
        if len(mpp[text.author.id].pastMoves) == 0:
            await text.reply("Your solo game has been aborted!")
            del mpp[text.author.id]
            return
        await text.reply(f"You have resigned your solo game. The secret number was ||{fun2.getRand(text)}||")
        del mpp[text.author.id]
    else:
        n = mpp[text.author.id].userTurn
        if (abs(n) == 1 or abs(n) == 10) and len(
                mpp[text.author.id].pastMoves) == 0:
            await text.reply(f"Your game against <@{mpp[text.author.id].opp}> has been aborted!")
            if mpp[text.author.id].opp in mpp:
                del mpp[mpp[text.author.id].opp]
            del mpp[text.author.id]
            return
        await text.reply(f"You have resigned the game against <@{mpp[text.author.id].opp}>")
        await winner(text, mpp[text.author.id].opp)
        print(len(mpp))
        if text.author.id in mpp and mpp[text.author.id].opp in mpp:
            del mpp[mpp[text.author.id].opp]
        if text.author.id in mpp:
            del mpp[text.author.id]


#################################################################################################################


async def offerDraw(text):
    if text.author.id not in mpp:
        await text.reply("You are not playing any game currently")
        return
    if text.author.id == mpp[text.author.id].opp:
        await text.reply("You can't offer draw in your solo game!")
        return
    if mpp[mpp[text.author.id].opp].draw is True:
        await drawn(text, True)
        return
    if len(mpp[text.author.id].pastMoves) == 0:
        await text.reply("You can't offer draw before the game starts!")
        return
    if mpp[text.author.id].draw is True:
        await text.reply("You have already offered a draw!")
        return
    await text.reply(f"<@{mpp[text.author.id].opp}> your opponent has offered a draw. You can accept the offer (**by .draw**), or continue guessing!")
    mpp[text.author.id].draw = True
