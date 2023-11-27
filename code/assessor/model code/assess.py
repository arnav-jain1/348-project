from stack import Stack
def assess(postfix):
    '''
    Takes in postfix expression in either list form, then
    assesses contents and prints out the result of the expression.
    '''
    solution = Stack() # initialises a stack to append postfix contents onto and solve.
    
    for entry in postfix: # iterates through and assesses 
    
        if type(entry) == int: # Checks if entry is an integer
            solution.push(entry) # Appends integer to stack to be further assessed

        elif entry == '*': # Checks if entry is the multiplication operator
            multiplier = solution.peek().entry # sets the last node's entry as the multiplier
            solution.pop() # pops last node in stack
            multiplicand = solution.peek().entry # sets new last node's entry as  the multiplicand
            solution.pop() # pops last node in stack
            solution.push(multiplicand*multiplier) # multiplies both and adds result to stack for further assessment

        # Same method follows for all other operations
        elif entry == '/':
            divisor = solution.peek().entry
            solution.pop()
            dividend = solution.peek().entry
            solution.pop()
            solution.push(dividend/divisor)

        elif entry == '%':
            divisor = solution.peek().entry
            solution.pop()
            dividend = solution.peek().entry
            solution.pop()
            solution.push(dividend/divisor)

        elif entry == '+':
            addend1 = solution.peek().entry
            solution.pop()
            addend2 = solution.peek().entry
            solution.pop()
            solution.push(addend1+addend2)

        elif entry == '-':
            subtrahend = solution.peek().entry
            solution.pop()
            minuend = solution.peek().entry
            solution.pop()
            solution.push(minuend-subtrahend)

        elif entry == '^':
            power = solution.peek().entry
            solution.pop()
            base = solution.peek().entry
            solution.pop()
            solution.push(base**power)   
     
    print(f'Result: {solution.peek().entry}') # Prints result, may just return result

# Testing
postfix = [12,2,3,4,5,'-','+','^','+'] # Test Expression: (2^(4-5+3))+12, Expected Result: 16
assess(postfix) # Returns 16, as expected