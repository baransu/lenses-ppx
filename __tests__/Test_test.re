open Jest;
open Expect;

module State = [%lenses
  type state = {
    email: string,
    age: int,
  }
];

let state: State.state = {email: "test@test.com", age: 0};

describe("lenses-ppx", () => {
  test("should match snapshot", () =>
    state |> expect |> toMatchSnapshot
  );

  test("should get email", () =>
    State.(state->get(Email)) |> expect |> toBe("test@test.com")
  );
  test("should get age", () =>
    State.(state->get(Age)) |> expect |> toBe(0)
  );

  test("should set email", () => {
    let {email}: State.state = State.(state->set(Email, "other@test.com"));
    email |> expect |> toBe("other@test.com");
  });

  test("should set age", () => {
    let age = State.(state->set(Age, 10)->get(Age));
    age |> expect |> toBe(10);
  });
});
