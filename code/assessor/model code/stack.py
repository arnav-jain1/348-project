from node import Node
class Stack:
    def __init__(self):
        '''
        Sets the default value for the top of a stack to None
        '''
        self._top = None
    def push(self, entry):
        '''
        Adds a new entry to the top of a given stack
        '''
        new_node = Node(entry)
        new_node.next = self._top
        self._top = new_node
    def pop(self):
        '''
        Deletes the top value of a given stacks and checks whether or not
        a deletion can take place given whether or not the stack is empty
        '''
        if not self.is_empty():
            current_top_value = self._top.entry
            self._top = self._top.next
            return current_top_value
        else:
            raise RuntimeError("Pop attempted on empty stack")
    def is_empty(self):
        '''
        Returns whether or not the given stack is empty
        '''
        if self._top == None:
            return True
        else:
            return False
    def peek(self):
        '''
        Returns the topmost node of the given stack
        '''
        return self._top
        