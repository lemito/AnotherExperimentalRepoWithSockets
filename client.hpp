#ifndef _CLIENT_H
#define _CLIENT_H

class client
{
public:
    client();
    client(client &&) = default;
    client(const client &) = default;
    client &operator=(client &&) = default;
    client &operator=(const client &) = default;
    ~client();

private:
    
};

client::client()
{
}

client::~client()
{
}

#endif