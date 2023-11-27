class Node():
    def __init__(self, entry):
        '''
        Stores the entry and defaults the linked value to None
        unless further specified, further specifies a bidirectional method.
        '''
        self.entry = entry
        self.next = None
        self.bhnd = None