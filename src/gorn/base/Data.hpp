#ifndef __gorn__Data__
#define __gorn__Data__

#include <vector>
#include <memory>
#include <string>
#include <initializer_list>


namespace gorn
{
	class Data
	{
	private:
		std::vector<uint8_t> _mem;

	public:
		Data();
		Data(size_t size);
		Data(const void* data, size_t size);
        Data(const std::string& data);
		Data(const Data& other);
		Data(Data&& other);
        
        template<typename T>
        Data(std::initializer_list<T> list);

        template<typename T>
		Data(const std::vector<T>& data);

        template<typename T>
		Data(std::vector<T>&& data);

        Data& operator=(Data&& other);
        Data& operator=(const Data& other);

		uint8_t* ptr();
		const uint8_t* ptr() const;
        std::vector<uint8_t>& mem();
        const std::vector<uint8_t>& mem() const;
		size_t size() const;
        bool empty() const;


        static Data readFile(const std::string& path);

        friend class DataInputStream;
        friend class DataOutputStream;
	};

    template<typename T>
    Data::Data(std::initializer_list<T> list):
    _mem(reinterpret_cast<const uint8_t*>(list.begin()),
        reinterpret_cast<const uint8_t*>(list.end()))
    {
    }

    template<typename T>
	Data::Data(const std::vector<T>& data):
	_mem(reinterpret_cast<const uint8_t*>(&data.front()),
        reinterpret_cast<const uint8_t*>(&data.back()))
	{
	}

    template<typename T>
	Data::Data(std::vector<T>&& data):
	_mem(reinterpret_cast<const uint8_t*>(&data.front()),
        reinterpret_cast<const uint8_t*>(&data.back()))
	{
	}

    class DataOutputStream;

    class DataInputStream
    {
	protected:
		const Data& _data;
		size_t _read;
	public:
		DataInputStream(const Data& data);

		size_t read(uint8_t* s, size_t n);
		size_t read(DataOutputStream& s, size_t n);
		size_t read(Data& s, size_t n);
        size_t read(std::string& s, char end='\n');
        bool reachedEnd() const;
    };

    class DataOutputStream
    {
    protected:
		Data& _data;
		mutable size_t _write;

        bool fit(size_t n);
	public:
		DataOutputStream(Data& data);

		size_t write(size_t n);
		size_t write(const uint8_t* s, size_t n);
		size_t write(const Data& s, size_t n, size_t start=0);
		size_t write(DataInputStream& s, size_t n);
        size_t write(const std::string& s);
    };
}

#endif
