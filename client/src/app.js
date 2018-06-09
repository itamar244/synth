// @flow
import Environment from './env';
import App from './ui/app';

const env = new Environment();
let detach = null;

const root = document.querySelector('#root');
if (root !== null) {
  root.append(new App(env));
}
