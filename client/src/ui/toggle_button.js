// @flow
type Handlers<Key> = { +[Key]: ?() => mixed };

export default class ToggleButton<Option: string> extends HTMLElement {
  index: number = 0;
  options: Option[];
  handlers: Handlers<Option>;
  button = document.createElement('button');

  constructor(
    options: Option[],
    handlers: Handlers<Option>,
  ) {
    super();
    this.options = options;
    this.handlers = handlers;
    this.append(this.button);
    this.paint();

    this.addEventListener('click', () => {
      this.index =
        this.index === this.options.length - 1 ? 0 : this.index + 1;
      this.paint();
    });
  }

  paint() {
    const handler = this.handlers[this.options[this.index]];
    if (handler != null) {
      handler();
    }

    this.button.textContent =
      `Switch to ${this.options[this.index]}`;
  }
}

customElements.define('toggle-button', ToggleButton);
