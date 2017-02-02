/*
 * containers.hpp
 *
 *  Created on: 23 sept. 2016
 *      Author: padget
 */

#ifndef THODD_CONTAINERS_HPP_
#  define THODD_CONTAINERS_HPP_

#  include <thodd/meta.hpp>
#  include <thodd/require.hpp>
#  include <thodd/law.hpp>
#  include <thodd/tuple.hpp>
#  include <thodd/functional.hpp>
#  include <thodd/container_func.hpp>
#  include <thodd/container_dsl.hpp>
#  include <thodd/container_range.hpp>

#  include <initializer_list>


namespace thodd
{
    



    /// /// ///
    /// Set ///
    /// /// ///
  






   

   


  




//	template<
//		typename colname_t,
//		typename item_t>
//	struct column
//	{
//		item_t m_item;
//
//
//	public:
//		item_t&
//		get()
//		{
//			return m_item;
//		}
//
//
//		item_t const&
//		get() const
//		{
//			return m_item;
//		}
//
//
//	public:
//		column() = default;
//		column(column const&) = default;
//		column(column&&) = default;
//		virtual ~column() = default;
//		column& operator=(column const&) = default;
//		column& operator=(column&&) = default;
//
//
//	public:
//		column(
//			item_t const& _item):
//			m_item{_item} {}
//
//
//		template<
//			typename uitem_t>
//		column(
//			uitem_t&& _uitem):
//			m_item{perfect<uitem_t>(_uitem)} {}
//	};
//
//
//	template<
//		typename ... columns_t>
//	class record;
//
//
//	template<
//		typename ... colnames_t,
//		typename ... items_t>
//	class record<column<colnames_t, items_t>...>:
//		public column<colnames_t, items_t>...
//	{
//		template<
//			typename colname_t>
//		using at_ = model::value_of_<
//						model::map<model::pair<colnames_t, items_t>...>,
//						colname_t>;
//
//	public:
//		template<
//			typename colname_t>
//		inline at_<colname_t>&
//		get()
//		{
//			return column<colname_t, at_<colname_t>>::get();
//		}
//
//		template<
//			typename colname_t>
//		inline at_<colname_t> const&
//		get() const
//		{
//			return column<colname_t, at_<colname_t>>::get();
//		}
//
//
//	public:
//		record() = default;
//		record(record const&) = default;
//		record(record&&) = default;
//		virtual ~record() = default;
//		record& operator=(record const&) = default;
//		record& operator=(record&&) = default;
//
//		record(
//			items_t const&... _items):
//			column<colnames_t, items_t>(_items)... {}
//
//		template<
//			typename ... uitems_t>
//		record(
//			uitems_t&&... _uitems):
//			column<colnames_t, items_t>(perfect<uitems_t>(_uitems))... {}
//
//		template<
//			typename ... uitems_t>
//		record(
//			record<uitems_t..., colnames_t...>&& _urecord):
//			column<colnames_t, items_t>(_urecord.template get<uitems_t, colnames_t>())... {}
//
//		template<
//			typename ... uitems_t>
//		record(
//			record<uitems_t..., colnames_t...> const& _urecord):
//			column<colnames_t, items_t>(_urecord.template get<uitems_t, colnames_t>())... {}
//	};
//
//
//	template<
//		typename record_t>
//	class table;
//
//	template<
//		typename ... colnames_t,
//		typename ... items_t>
//	class table<record<column<colnames_t, items_t>...>>
//	{
//		using record_t = record<column<colnames_t, items_t>...>;
//		using table_iterator = typename list<record_t>::list_iterator;
//
//		list<record_t> m_content;
//
//	public:
//		table() = default;
//		table(table const&) = default;
//		table(table&&) = default;
//		~table() = default;
//		table& operator=(table const&) = default;
//		table& operator=(table&&) = default;
//
//
//		template<
//			typename iterator_t>
//		explicit table(
//			iterator_t _begin,
//			iterator_t _end):
//			m_content{_begin, _end} {}
//
//
//		explicit table(
//			std::initializer_list<record_t> _init):
//			table<record<column<colnames_t, items_t>...>>{_init.begin(), _init.end()} {}
//
//
//		template<
//			typename container_t>
//		explicit table(
//			container_t&& _container):
//			table<record<column<colnames_t, items_t>...>>{_container.begin(), _container.end()} {}
//
//
//		template<
//			typename iterator_t>
//		table&
//		operator=(
//			tuple<iterator_t, iterator_t>&& _range)
//		{
//			m_content = _range;
//			return *this;
//		}
//
//
//		table&
//		operator=(
//			std::initializer_list<record_t> _range)
//		{
//			return this->operator =(make_tuple(_range.begin(), _range.end()));
//		}
//
//
//		template<
//			typename container_t>
//		table&
//		operator=(
//			container_t&& _container)
//		{
//			return this->operator =(make_tuple(_container.begin(), _container.end()));
//		}
//
//
//
//	public:
//		inline table_iterator const
//		begin() const
//		{
//			return m_content.begin();
//		}
//
//
//		inline table_iterator
//		begin()
//		{
//			return m_content.begin();
//		}
//
//
//		inline table_iterator const
//		end() const
//		{
//			return m_content.end();
//		}
//
//
//		inline table_iterator
//		end()
//		{
//			return m_content.end();
//		}
//
//		inline void
//		clear()
//		{
//			m_content.clear();
//		}
//
//		inline size_t const
//		size() const
//		{
//			return m_content.size();
//		}
//
//	public:
//		inline void
//		push_at(
//			record_t const& _record,
//			table_iterator _pos)
//		{
//			m_content.push_at(_record, _pos);
//		}
//
//		inline void
//		push_at(
//			record_t&& _record,
//			table_iterator _pos)
//		{
//			m_content.push_at(_record, _pos);
//		}
//
//		inline table_iterator
//		pop_at(
//			table_iterator _pos)
//		{
//			return m_content.pop_at(_pos);
//		}
//	};

}

#endif /* THODD_CONTAINERS_HPP_ */
