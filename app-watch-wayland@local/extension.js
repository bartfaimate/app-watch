import Gio from "gi://Gio";
import { Extension } from "resource:///org/gnome/shell/extensions/extension.js";
import * as Main from "resource:///org/gnome/shell/ui/main.js";


const NAME = "app-watch-wayland"; 

const warn = (data) => {
  console.warn(`[${NAME}]` + data)
}

const log = (data) => {
  console.log(`[${NAME}]` + data)
}


export default class AppWatch extends Extension {
  socket = null;

  constructor(metadata) {
    super(metadata);

    console.debug(`constructing ${this.metadata.name}`);
  }

  enable() {
    try {
      this.socket = Gio.SocketClient.new().connect_to_host(
        "127.0.0.1",
        7777,
        null,
      );
    } catch (e) {
      warn("socket connect failed");
    }

    global.display.connect("notify::focus-window", () => {
      let win = global.display.focus_window;
      if (!win) return;

      let app = win.get_wm_class();
      if (app) {
        this.sendApp(app);
      }
    });

    Main.notify("AppWatch", "Loaded");
  }

  disable() {
    this.socket = null;
  }

  sendApp(app) {
    // Main.notify("AppWatch", app);

    try {
      if (!this.socket) {
        this.socket = Gio.SocketClient.new().connect_to_host(
        "127.0.0.1",
        7777,
        null,
      );
    }
    this.socket.get_output_stream().write_all(app + "\n", null);

    } catch (e) {
      warn(e);
    }
  }
}
