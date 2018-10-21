# jambe

Experimental url router for NodeJS writtin in C++ using N-API.

## Implementation

Instead of using a Trie, the route is tokenize using slash
as a separator. This make the router slower but the code
is extremely simpler.

For instance, the routes `/users/:id`, `/users/me`, `/utilities`, create the following tree:

                   /    
          ---------|--------
          |                |
        users          utilities
        |   |
       me  :id
       
Possible routes conflicts like `/users/me` with `/users/:id/posts`
are working using backtracking.

## Usage

- compile C++ test binary: make -C cpp/jambe bin-debug
- launch tests:            make -C cpp/jambe check
- compile addon:           yarn install && yarn build
