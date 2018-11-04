# jambe

Experimental url router for NodeJS writtin in C++ using N-API.

Performance is not good because there is a huge overhead when calling native code from Javascript.
A url router is not a good use case of N-API.

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

- compile addon: `yarn install && yarn build`
