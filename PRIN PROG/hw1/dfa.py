#!/usr/bin/env python3


def constructDFA(states, symbols, rules):
    rulesList = []
    for i in range(0, len(rules)):
        rulesList.append(
            [rules[i].split()[0], rules[i].split()[2], rules[i].split()[4]])
    dfa = {}
    for i in range(len(states)):
        list = {}
        for j in range(len(rulesList)):
            if rulesList[j][0] == states[i]:
                list[rulesList[j][2]] = rulesList[j][1]
        if list != {}:
            dfa[states[i]] = list
    return dfa


def accepts(string, start, final, dfa):
    state = start[0]
    for c in string:
        if state in dfa:
            state = dfa[state][c]
        else:
            return False
    return state in final


def main():
    try:
        states = input().split()  # Number of rows
        symbols = input().split()  # Entries in rows
        del states[0]
        del symbols[0]
        rules = []  # Order of entries in rows
        start = 0
        final = 0
        loop = "begin_rules"
        while loop != "end_rules":
            if loop != "begin_rules":
                rules.append(loop)
            loop = input()

        start = input().split()
        final = input().split()
        del start[0]
        del final[0]
        dfa = constructDFA(states, symbols, rules)
        try:
            while True:
                string = input()
                if accepts(string, start, final, dfa) == True:
                    print("accepted")
                else:
                    print("rejected")
        except EOFError:
            return

    except EOFError:
        return


if __name__ == "__main__":
    main()
