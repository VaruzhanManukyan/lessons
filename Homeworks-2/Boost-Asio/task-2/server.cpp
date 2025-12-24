#include <boost/asio.hpp>
#include <thread>
#include <iostream>
#include <chrono>
#include <iomanip>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
private:
    tcp::socket socket;
    boost::asio::steady_timer timer;
    boost::asio::strand<tcp::socket::executor_type> strand;
    std::array<char, 1024> data;

    void do_read() {
        std::shared_ptr<Session> self = shared_from_this();

        timer.expires_after(std::chrono::seconds(30));
        timer.async_wait([this, self](boost::system::error_code error_code) {
                if (error_code == boost::asio::error::operation_aborted) {
                    return;
                }
                if (!error_code) {
                    std::cout << "Client timeout, disconnecting\n";
                    self->socket.close();
                }
            }
        );

        socket.async_read_some(
            boost::asio::buffer(data),
            boost::asio::bind_executor(
                strand,
                [this, self](boost::system::error_code error_code, std::size_t length) {
                    if (!error_code && length > 0) {
                        do_write(length);
                    } else {
                        std::cerr << "[!] Read error: " << error_code.message() << "\n";
                    }
                }
            )
        );
    }

    void do_write(std::size_t lenght) {
        std::shared_ptr<Session> self = shared_from_this();

        boost::asio::async_write(
            socket,
            boost::asio::buffer(data, lenght),
            boost::asio::bind_executor(
                strand,
                [this, self](boost::system::error_code error_code, std::size_t length) {
                    if (!error_code && length > 0) {
                        timer.cancel();
                        std::cout << "Client write: " << std::string(data.data(), length) << "\n";
                        do_read();
                    } else {
                        std::cerr << "[!] Write error: " << error_code.message() << "\n";
                    }
                }
            )
        );
    }
public:
    explicit Session(tcp::socket socket): socket(std::move(socket)), timer(socket.get_executor()), strand(socket.get_executor()) {
        try {
            boost::asio::ip::basic_endpoint<tcp> endpoint = socket.remote_endpoint();
            std::cout << "[+] Client connected: " << endpoint.address().to_string() << ":" << endpoint.port() << "\n";
        } catch (...) {
            std::cout << "[+] Client connected (unknown endpoint)\n";
        }
    }

    ~Session() {
        try {
            boost::asio::ip::basic_endpoint<tcp> endpoint = socket.remote_endpoint();
            std::cout << "[-] Client disconnected: " << endpoint.address().to_string() << ":" << endpoint.port() << "\n";
        } catch (...) {
            std::cout << "[-] Client disconnected\n";
        }
    }

    void start() {
        do_read();
    }
};

class Server {
private:
    boost::asio::io_context& io_context;
    tcp::acceptor acceptor;

    void do_accept() {
        acceptor.async_accept(
            [this](boost::system::error_code error_code, tcp::socket socket) {
                if (!error_code) {
                    std::make_shared<Session>(std::move(socket))->start();
                } else {
                    std::cerr << "[!] Accept error: " << error_code.message() << "\n";
                }

                do_accept();
            }
        );
    }
public:
    Server(boost::asio::io_context& io_context, std::size_t port):
    io_context(io_context),
    acceptor(io_context, tcp::endpoint(tcp::v4(), port)) {
        std::cout << "[*] Server listening on port " << port << "\n";
        do_accept();
    }
};

int main() {
    try {
        const std::size_t port = 8080;
        boost::asio::io_context io_context;

        Server server(io_context, port);
        std::size_t number_of_threads = std::thread::hardware_concurrency();
        if (number_of_threads == 0) {
            number_of_threads = 4;
        }

        std::cout << "[*] Starting IO threads: " << number_of_threads << "\n";

        std::vector<std::thread> threads;
        threads.reserve(number_of_threads);

        for (std::size_t i = 0; i < number_of_threads; ++i) {
            threads.emplace_back([&io_context, i]() {
                    std::cout << "[*] Worker thread started: #" << i << "\n";
                    io_context.run();
                }
            );
        }

        for (std::thread& thread : threads) {
            thread.join();
        }

    } catch (std::exception& exception) {
        std::cerr << "[FATAL] Exception: " << exception.what() << "\n";
    }

    return 0;
}