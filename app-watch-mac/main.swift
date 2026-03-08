import AppKit
import Network

class AppWatcher {

    private var connection: NWConnection?

    init() {
        connect()

        let center = NSWorkspace.shared.notificationCenter
        center.addObserver(
            self,
            selector: #selector(appChanged(_:)),
            name: NSWorkspace.didActivateApplicationNotification,
            object: nil
        )
    }

    private func connect() {

        let host = NWEndpoint.Host("127.0.0.1")
        let port = NWEndpoint.Port(integerLiteral: 7777)

        connection = NWConnection(host: host, port: port, using: .tcp)

        connection?.stateUpdateHandler = { state in
            switch state {

            case .ready:
                print("TCP connected")

            case .failed(let error):
                print("Connection failed:", error)

            case .waiting(let error):
                print("Waiting:", error)

            default:
                break
            }
        }

        connection?.start(queue: .global())
    }

    private func send(_ msg: String) {

        guard let conn = connection else { return }

        let data = (msg + "\n").data(using: .utf8)!

        conn.send(content: data, completion: .contentProcessed { error in
            if let error = error {
                print("Send error:", error)
            }
        })
    }

    @objc func appChanged(_ notification: Notification) {

        guard let app =
            notification.userInfo?[NSWorkspace.applicationUserInfoKey]
            as? NSRunningApplication else { return }

        let bundle = app.bundleIdentifier ?? "unknown"

        print("Active:", bundle)

        send(bundle)
    }
}

let watcher = AppWatcher()
RunLoop.main.run()