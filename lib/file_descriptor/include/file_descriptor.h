//
// Created by kira on 3/23/20.
//

#ifndef PROJECT_INCLUDE_FILE_DESCRIPTOR_H_
#define PROJECT_INCLUDE_FILE_DESCRIPTOR_H_

namespace fd {
enum IO : int {
    READ, WRITE
};

class FileDescriptor {
 public:
    FileDescriptor();
    explicit FileDescriptor(int fd);
    FileDescriptor(FileDescriptor &&other) noexcept;
    ~FileDescriptor();

    [[nodiscard]] int fd() const;
    void close();
    void link(FileDescriptor const &other);

    FileDescriptor &operator=(FileDescriptor &&other) noexcept;

 private:
    int _fd;
};

class Pipe {
 public:
    Pipe();
    [[nodiscard]] const FileDescriptor &read() const;
    FileDescriptor &&read();
    [[nodiscard]] const FileDescriptor &write() const;
    FileDescriptor &&write();
 private:
    FileDescriptor _read;
    FileDescriptor _write;
};
}  // namespace fd


#endif  // PROJECT_INCLUDE_FILE_DESCRIPTOR_H_
