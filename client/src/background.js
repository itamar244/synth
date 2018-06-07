// @flow
import path from 'path';
import url from 'url';
import { app } from 'electron';
import createWindow from './helpers/window';

app.on('ready', () => {
  const mainWindow = createWindow('main', {
    width: 1000,
    height: 600
  });

  mainWindow.loadURL(
    url.format({
      pathname: path.join(__dirname, 'app.html'),
      protocol: 'file:',
      slashes: true
    })
  );
});

app.on('window-all-closed', () => {
  app.quit();
});
