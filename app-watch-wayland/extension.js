import Gio from "gi://Gio";
import { Extension } from "resource:///org/gnome/shell/extensions/extension.js";
import * as Main from "resource:///org/gnome/shell/ui/main.js";
import * as MessageTray from "resource:///org/gnome/shell/ui/messageTray.js";

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
        5555,
        null,
      );
    } catch (e) {
      log("socket connect failed");
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
    Main.notify("AppWatch", app);

    try {
      if (this.socket)
        this.socket.get_output_stream().write_all(app + "\n", null);
    } catch (e) {
      log(e);
    }
  }
}
