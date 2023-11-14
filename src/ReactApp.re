module Foo = {
  [@react.component]
  let make = (~name) => <div>
    {React.string("Hello " ++ name ++ "!")}
  </div>
}

module Counter = {
  [@react.component]
  let make = (~count: int) => {
    let c = switch count {
      | 1 => "once"
      | 2 => "twice"
      | n => Belt.Int.toString(n) ++ " times"
    };
    
    <div>{React.string(c)}</div>
  }
}

module App = {
  // This sample forces an import of Belt.*, so that CI builds can ensure that
  // Melange has been installed correctly for JS bundlers to be able to find it.
  [@react.component]
  let make = () => {
    let (c, setC) = React.useState(() => 0);

    <div>
      {["Hello " ++ World.name ++ "!", "This is React!"]
      ->Belt.List.map(greeting => <h1> greeting->React.string </h1>)
      ->Belt.List.toArray
      ->React.array}

      <Foo name="Alex" />
      <Counter count={c} />
      <button onClick={_ => setC(c => c + 1)}>{"Click Me"->React.string}</button>
    </div>
  }
    
};

ReactDOM.querySelector("#root")
->(
    fun
    | Some(root) => ReactDOM.render(<App />, root)
    | None =>
      Js.Console.error(
        "Failed to start React: couldn't find the #root element",
      )
  );
