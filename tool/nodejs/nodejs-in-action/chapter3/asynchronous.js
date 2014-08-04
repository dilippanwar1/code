// There are two popular models in the Node world for managing response
// logic: callbacks and event listeners.



// A callback is a function, passed as an argument to an asynchronous function,
// that describes what to do after the asynchronous operation has completed.
// Callbacks are used frequently in Node development, more so than event emitters.
//
// Node's built-in modules often utilize callbacks with two arguments: one
// argument for an error, should one occur, and one argument for results. The
// error  argument is often abbreviated as "er" or "err".



// Event emitters are entities that manage event listeners and allow events to
// be triggered. Some important Node API components, such as HTTP servers,
// TCP/IP servers, and streams, are implemented as event emitters and you can
// create your own for your own application needs.
//
// As we mentioned earlier, event responses are handled through the use of
// "listeners." A listener is the association of an event type with an
// asynchronous callback that gets triggered each time the event type occurs.

