// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_optimize_for.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5foptimize_5ffor_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5foptimize_5ffor_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3015000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3015003 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "google/protobuf/unittest.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2funittest_5foptimize_5ffor_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_google_2fprotobuf_2funittest_5foptimize_5ffor_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_google_2fprotobuf_2funittest_5foptimize_5ffor_2eproto;
::PROTOBUF_NAMESPACE_ID::Metadata descriptor_table_google_2fprotobuf_2funittest_5foptimize_5ffor_2eproto_metadata_getter(int index);
namespace protobuf_unittest {
class TestOptimizedForSize;
struct TestOptimizedForSizeDefaultTypeInternal;
extern TestOptimizedForSizeDefaultTypeInternal _TestOptimizedForSize_default_instance_;
class TestOptionalOptimizedForSize;
struct TestOptionalOptimizedForSizeDefaultTypeInternal;
extern TestOptionalOptimizedForSizeDefaultTypeInternal _TestOptionalOptimizedForSize_default_instance_;
class TestRequiredOptimizedForSize;
struct TestRequiredOptimizedForSizeDefaultTypeInternal;
extern TestRequiredOptimizedForSizeDefaultTypeInternal _TestRequiredOptimizedForSize_default_instance_;
}  // namespace protobuf_unittest
PROTOBUF_NAMESPACE_OPEN
template<> ::protobuf_unittest::TestOptimizedForSize* Arena::CreateMaybeMessage<::protobuf_unittest::TestOptimizedForSize>(Arena*);
template<> ::protobuf_unittest::TestOptionalOptimizedForSize* Arena::CreateMaybeMessage<::protobuf_unittest::TestOptionalOptimizedForSize>(Arena*);
template<> ::protobuf_unittest::TestRequiredOptimizedForSize* Arena::CreateMaybeMessage<::protobuf_unittest::TestRequiredOptimizedForSize>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace protobuf_unittest {

// ===================================================================

class TestOptimizedForSize PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:protobuf_unittest.TestOptimizedForSize) */ {
 public:
  inline TestOptimizedForSize() : TestOptimizedForSize(nullptr) {}
  virtual ~TestOptimizedForSize();
  explicit constexpr TestOptimizedForSize(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  TestOptimizedForSize(const TestOptimizedForSize& from);
  TestOptimizedForSize(TestOptimizedForSize&& from) noexcept
    : TestOptimizedForSize() {
    *this = ::std::move(from);
  }

  inline TestOptimizedForSize& operator=(const TestOptimizedForSize& from) {
    CopyFrom(from);
    return *this;
  }
  inline TestOptimizedForSize& operator=(TestOptimizedForSize&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const TestOptimizedForSize& default_instance() {
    return *internal_default_instance();
  }
  enum FooCase {
    kIntegerField = 2,
    kStringField = 3,
    FOO_NOT_SET = 0,
  };

  static inline const TestOptimizedForSize* internal_default_instance() {
    return reinterpret_cast<const TestOptimizedForSize*>(
               &_TestOptimizedForSize_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(TestOptimizedForSize& a, TestOptimizedForSize& b) {
    a.Swap(&b);
  }
  inline void Swap(TestOptimizedForSize* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TestOptimizedForSize* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline TestOptimizedForSize* New() const final {
    return CreateMaybeMessage<TestOptimizedForSize>(nullptr);
  }

  TestOptimizedForSize* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<TestOptimizedForSize>(arena);
  }
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(TestOptimizedForSize* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "protobuf_unittest.TestOptimizedForSize";
  }
  protected:
  explicit TestOptimizedForSize(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    return ::descriptor_table_google_2fprotobuf_2funittest_5foptimize_5ffor_2eproto_metadata_getter(kIndexInFileMessages);
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMsgFieldNumber = 19,
    kIFieldNumber = 1,
    kIntegerFieldFieldNumber = 2,
    kStringFieldFieldNumber = 3,
  };
  // optional .protobuf_unittest.ForeignMessage msg = 19;
  bool has_msg() const;
  private:
  bool _internal_has_msg() const;
  public:
  void clear_msg();
  const ::protobuf_unittest::ForeignMessage& msg() const;
  ::protobuf_unittest::ForeignMessage* release_msg();
  ::protobuf_unittest::ForeignMessage* mutable_msg();
  void set_allocated_msg(::protobuf_unittest::ForeignMessage* msg);
  private:
  const ::protobuf_unittest::ForeignMessage& _internal_msg() const;
  ::protobuf_unittest::ForeignMessage* _internal_mutable_msg();
  public:
  void unsafe_arena_set_allocated_msg(
      ::protobuf_unittest::ForeignMessage* msg);
  ::protobuf_unittest::ForeignMessage* unsafe_arena_release_msg();

  // optional int32 i = 1;
  bool has_i() const;
  private:
  bool _internal_has_i() const;
  public:
  void clear_i();
  ::PROTOBUF_NAMESPACE_ID::int32 i() const;
  void set_i(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_i() const;
  void _internal_set_i(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // int32 integer_field = 2;
  bool has_integer_field() const;
  private:
  bool _internal_has_integer_field() const;
  public:
  void clear_integer_field();
  ::PROTOBUF_NAMESPACE_ID::int32 integer_field() const;
  void set_integer_field(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_integer_field() const;
  void _internal_set_integer_field(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // string string_field = 3;
  bool has_string_field() const;
  private:
  bool _internal_has_string_field() const;
  public:
  void clear_string_field();
  const std::string& string_field() const;
  void set_string_field(const std::string& value);
  void set_string_field(std::string&& value);
  void set_string_field(const char* value);
  void set_string_field(const char* value, size_t size);
  std::string* mutable_string_field();
  std::string* release_string_field();
  void set_allocated_string_field(std::string* string_field);
  private:
  const std::string& _internal_string_field() const;
  void _internal_set_string_field(const std::string& value);
  std::string* _internal_mutable_string_field();
  public:

  GOOGLE_PROTOBUF_EXTENSION_ACCESSORS(TestOptimizedForSize)
  void clear_foo();
  FooCase foo_case() const;
  static const int kTestExtensionFieldNumber = 1234;
  static ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier< ::protobuf_unittest::TestOptimizedForSize,
      ::PROTOBUF_NAMESPACE_ID::internal::PrimitiveTypeTraits< ::PROTOBUF_NAMESPACE_ID::int32 >, 5, false >
    test_extension;
  static const int kTestExtension2FieldNumber = 1235;
  static ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier< ::protobuf_unittest::TestOptimizedForSize,
      ::PROTOBUF_NAMESPACE_ID::internal::MessageTypeTraits< ::protobuf_unittest::TestRequiredOptimizedForSize >, 11, false >
    test_extension2;
  // @@protoc_insertion_point(class_scope:protobuf_unittest.TestOptimizedForSize)
 private:
  class _Internal;
  void set_has_integer_field();
  void set_has_string_field();

  inline bool has_foo() const;
  inline void clear_has_foo();

  ::PROTOBUF_NAMESPACE_ID::internal::ExtensionSet _extensions_;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::protobuf_unittest::ForeignMessage* msg_;
  ::PROTOBUF_NAMESPACE_ID::int32 i_;
  union FooUnion {
    constexpr FooUnion() : _constinit_{} {}
      ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized _constinit_;
    ::PROTOBUF_NAMESPACE_ID::int32 integer_field_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr string_field_;
  } foo_;
  ::PROTOBUF_NAMESPACE_ID::uint32 _oneof_case_[1];

  friend struct ::TableStruct_google_2fprotobuf_2funittest_5foptimize_5ffor_2eproto;
};
// -------------------------------------------------------------------

class TestRequiredOptimizedForSize PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:protobuf_unittest.TestRequiredOptimizedForSize) */ {
 public:
  inline TestRequiredOptimizedForSize() : TestRequiredOptimizedForSize(nullptr) {}
  virtual ~TestRequiredOptimizedForSize();
  explicit constexpr TestRequiredOptimizedForSize(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  TestRequiredOptimizedForSize(const TestRequiredOptimizedForSize& from);
  TestRequiredOptimizedForSize(TestRequiredOptimizedForSize&& from) noexcept
    : TestRequiredOptimizedForSize() {
    *this = ::std::move(from);
  }

  inline TestRequiredOptimizedForSize& operator=(const TestRequiredOptimizedForSize& from) {
    CopyFrom(from);
    return *this;
  }
  inline TestRequiredOptimizedForSize& operator=(TestRequiredOptimizedForSize&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const TestRequiredOptimizedForSize& default_instance() {
    return *internal_default_instance();
  }
  static inline const TestRequiredOptimizedForSize* internal_default_instance() {
    return reinterpret_cast<const TestRequiredOptimizedForSize*>(
               &_TestRequiredOptimizedForSize_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(TestRequiredOptimizedForSize& a, TestRequiredOptimizedForSize& b) {
    a.Swap(&b);
  }
  inline void Swap(TestRequiredOptimizedForSize* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TestRequiredOptimizedForSize* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline TestRequiredOptimizedForSize* New() const final {
    return CreateMaybeMessage<TestRequiredOptimizedForSize>(nullptr);
  }

  TestRequiredOptimizedForSize* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<TestRequiredOptimizedForSize>(arena);
  }
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(TestRequiredOptimizedForSize* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "protobuf_unittest.TestRequiredOptimizedForSize";
  }
  protected:
  explicit TestRequiredOptimizedForSize(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    return ::descriptor_table_google_2fprotobuf_2funittest_5foptimize_5ffor_2eproto_metadata_getter(kIndexInFileMessages);
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kXFieldNumber = 1,
  };
  // required int32 x = 1;
  bool has_x() const;
  private:
  bool _internal_has_x() const;
  public:
  void clear_x();
  ::PROTOBUF_NAMESPACE_ID::int32 x() const;
  void set_x(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_x() const;
  void _internal_set_x(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:protobuf_unittest.TestRequiredOptimizedForSize)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::int32 x_;
  friend struct ::TableStruct_google_2fprotobuf_2funittest_5foptimize_5ffor_2eproto;
};
// -------------------------------------------------------------------

class TestOptionalOptimizedForSize PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:protobuf_unittest.TestOptionalOptimizedForSize) */ {
 public:
  inline TestOptionalOptimizedForSize() : TestOptionalOptimizedForSize(nullptr) {}
  virtual ~TestOptionalOptimizedForSize();
  explicit constexpr TestOptionalOptimizedForSize(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  TestOptionalOptimizedForSize(const TestOptionalOptimizedForSize& from);
  TestOptionalOptimizedForSize(TestOptionalOptimizedForSize&& from) noexcept
    : TestOptionalOptimizedForSize() {
    *this = ::std::move(from);
  }

  inline TestOptionalOptimizedForSize& operator=(const TestOptionalOptimizedForSize& from) {
    CopyFrom(from);
    return *this;
  }
  inline TestOptionalOptimizedForSize& operator=(TestOptionalOptimizedForSize&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const TestOptionalOptimizedForSize& default_instance() {
    return *internal_default_instance();
  }
  static inline const TestOptionalOptimizedForSize* internal_default_instance() {
    return reinterpret_cast<const TestOptionalOptimizedForSize*>(
               &_TestOptionalOptimizedForSize_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(TestOptionalOptimizedForSize& a, TestOptionalOptimizedForSize& b) {
    a.Swap(&b);
  }
  inline void Swap(TestOptionalOptimizedForSize* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TestOptionalOptimizedForSize* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline TestOptionalOptimizedForSize* New() const final {
    return CreateMaybeMessage<TestOptionalOptimizedForSize>(nullptr);
  }

  TestOptionalOptimizedForSize* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<TestOptionalOptimizedForSize>(arena);
  }
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(TestOptionalOptimizedForSize* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "protobuf_unittest.TestOptionalOptimizedForSize";
  }
  protected:
  explicit TestOptionalOptimizedForSize(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    return ::descriptor_table_google_2fprotobuf_2funittest_5foptimize_5ffor_2eproto_metadata_getter(kIndexInFileMessages);
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kOFieldNumber = 1,
  };
  // optional .protobuf_unittest.TestRequiredOptimizedForSize o = 1;
  bool has_o() const;
  private:
  bool _internal_has_o() const;
  public:
  void clear_o();
  const ::protobuf_unittest::TestRequiredOptimizedForSize& o() const;
  ::protobuf_unittest::TestRequiredOptimizedForSize* release_o();
  ::protobuf_unittest::TestRequiredOptimizedForSize* mutable_o();
  void set_allocated_o(::protobuf_unittest::TestRequiredOptimizedForSize* o);
  private:
  const ::protobuf_unittest::TestRequiredOptimizedForSize& _internal_o() const;
  ::protobuf_unittest::TestRequiredOptimizedForSize* _internal_mutable_o();
  public:
  void unsafe_arena_set_allocated_o(
      ::protobuf_unittest::TestRequiredOptimizedForSize* o);
  ::protobuf_unittest::TestRequiredOptimizedForSize* unsafe_arena_release_o();

  // @@protoc_insertion_point(class_scope:protobuf_unittest.TestOptionalOptimizedForSize)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::protobuf_unittest::TestRequiredOptimizedForSize* o_;
  friend struct ::TableStruct_google_2fprotobuf_2funittest_5foptimize_5ffor_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// TestOptimizedForSize

// optional int32 i = 1;
inline bool TestOptimizedForSize::_internal_has_i() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool TestOptimizedForSize::has_i() const {
  return _internal_has_i();
}
inline void TestOptimizedForSize::clear_i() {
  i_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 TestOptimizedForSize::_internal_i() const {
  return i_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 TestOptimizedForSize::i() const {
  // @@protoc_insertion_point(field_get:protobuf_unittest.TestOptimizedForSize.i)
  return _internal_i();
}
inline void TestOptimizedForSize::_internal_set_i(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  i_ = value;
}
inline void TestOptimizedForSize::set_i(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_i(value);
  // @@protoc_insertion_point(field_set:protobuf_unittest.TestOptimizedForSize.i)
}

// optional .protobuf_unittest.ForeignMessage msg = 19;
inline bool TestOptimizedForSize::_internal_has_msg() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || msg_ != nullptr);
  return value;
}
inline bool TestOptimizedForSize::has_msg() const {
  return _internal_has_msg();
}
inline const ::protobuf_unittest::ForeignMessage& TestOptimizedForSize::_internal_msg() const {
  const ::protobuf_unittest::ForeignMessage* p = msg_;
  return p != nullptr ? *p : reinterpret_cast<const ::protobuf_unittest::ForeignMessage&>(
      ::protobuf_unittest::_ForeignMessage_default_instance_);
}
inline const ::protobuf_unittest::ForeignMessage& TestOptimizedForSize::msg() const {
  // @@protoc_insertion_point(field_get:protobuf_unittest.TestOptimizedForSize.msg)
  return _internal_msg();
}
inline void TestOptimizedForSize::unsafe_arena_set_allocated_msg(
    ::protobuf_unittest::ForeignMessage* msg) {
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(msg_);
  }
  msg_ = msg;
  if (msg) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:protobuf_unittest.TestOptimizedForSize.msg)
}
inline ::protobuf_unittest::ForeignMessage* TestOptimizedForSize::release_msg() {
  _has_bits_[0] &= ~0x00000001u;
  ::protobuf_unittest::ForeignMessage* temp = msg_;
  msg_ = nullptr;
  if (GetArena() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
  return temp;
}
inline ::protobuf_unittest::ForeignMessage* TestOptimizedForSize::unsafe_arena_release_msg() {
  // @@protoc_insertion_point(field_release:protobuf_unittest.TestOptimizedForSize.msg)
  _has_bits_[0] &= ~0x00000001u;
  ::protobuf_unittest::ForeignMessage* temp = msg_;
  msg_ = nullptr;
  return temp;
}
inline ::protobuf_unittest::ForeignMessage* TestOptimizedForSize::_internal_mutable_msg() {
  _has_bits_[0] |= 0x00000001u;
  if (msg_ == nullptr) {
    auto* p = CreateMaybeMessage<::protobuf_unittest::ForeignMessage>(GetArena());
    msg_ = p;
  }
  return msg_;
}
inline ::protobuf_unittest::ForeignMessage* TestOptimizedForSize::mutable_msg() {
  // @@protoc_insertion_point(field_mutable:protobuf_unittest.TestOptimizedForSize.msg)
  return _internal_mutable_msg();
}
inline void TestOptimizedForSize::set_allocated_msg(::protobuf_unittest::ForeignMessage* msg) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(msg_);
  }
  if (msg) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(msg)->GetArena();
    if (message_arena != submessage_arena) {
      msg = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, msg, submessage_arena);
    }
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  msg_ = msg;
  // @@protoc_insertion_point(field_set_allocated:protobuf_unittest.TestOptimizedForSize.msg)
}

// int32 integer_field = 2;
inline bool TestOptimizedForSize::_internal_has_integer_field() const {
  return foo_case() == kIntegerField;
}
inline bool TestOptimizedForSize::has_integer_field() const {
  return _internal_has_integer_field();
}
inline void TestOptimizedForSize::set_has_integer_field() {
  _oneof_case_[0] = kIntegerField;
}
inline void TestOptimizedForSize::clear_integer_field() {
  if (_internal_has_integer_field()) {
    foo_.integer_field_ = 0;
    clear_has_foo();
  }
}
inline ::PROTOBUF_NAMESPACE_ID::int32 TestOptimizedForSize::_internal_integer_field() const {
  if (_internal_has_integer_field()) {
    return foo_.integer_field_;
  }
  return 0;
}
inline void TestOptimizedForSize::_internal_set_integer_field(::PROTOBUF_NAMESPACE_ID::int32 value) {
  if (!_internal_has_integer_field()) {
    clear_foo();
    set_has_integer_field();
  }
  foo_.integer_field_ = value;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 TestOptimizedForSize::integer_field() const {
  // @@protoc_insertion_point(field_get:protobuf_unittest.TestOptimizedForSize.integer_field)
  return _internal_integer_field();
}
inline void TestOptimizedForSize::set_integer_field(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_integer_field(value);
  // @@protoc_insertion_point(field_set:protobuf_unittest.TestOptimizedForSize.integer_field)
}

// string string_field = 3;
inline bool TestOptimizedForSize::_internal_has_string_field() const {
  return foo_case() == kStringField;
}
inline bool TestOptimizedForSize::has_string_field() const {
  return _internal_has_string_field();
}
inline void TestOptimizedForSize::set_has_string_field() {
  _oneof_case_[0] = kStringField;
}
inline void TestOptimizedForSize::clear_string_field() {
  if (_internal_has_string_field()) {
    foo_.string_field_.Destroy(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
    clear_has_foo();
  }
}
inline const std::string& TestOptimizedForSize::string_field() const {
  // @@protoc_insertion_point(field_get:protobuf_unittest.TestOptimizedForSize.string_field)
  return _internal_string_field();
}
inline void TestOptimizedForSize::set_string_field(const std::string& value) {
  _internal_set_string_field(value);
  // @@protoc_insertion_point(field_set:protobuf_unittest.TestOptimizedForSize.string_field)
}
inline std::string* TestOptimizedForSize::mutable_string_field() {
  // @@protoc_insertion_point(field_mutable:protobuf_unittest.TestOptimizedForSize.string_field)
  return _internal_mutable_string_field();
}
inline const std::string& TestOptimizedForSize::_internal_string_field() const {
  if (_internal_has_string_field()) {
    return foo_.string_field_.Get();
  }
  return ::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited();
}
inline void TestOptimizedForSize::_internal_set_string_field(const std::string& value) {
  if (!_internal_has_string_field()) {
    clear_foo();
    set_has_string_field();
    foo_.string_field_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  }
  foo_.string_field_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void TestOptimizedForSize::set_string_field(std::string&& value) {
  // @@protoc_insertion_point(field_set:protobuf_unittest.TestOptimizedForSize.string_field)
  if (!_internal_has_string_field()) {
    clear_foo();
    set_has_string_field();
    foo_.string_field_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  }
  foo_.string_field_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:protobuf_unittest.TestOptimizedForSize.string_field)
}
inline void TestOptimizedForSize::set_string_field(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  if (!_internal_has_string_field()) {
    clear_foo();
    set_has_string_field();
    foo_.string_field_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  }
  foo_.string_field_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{},
      ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:protobuf_unittest.TestOptimizedForSize.string_field)
}
inline void TestOptimizedForSize::set_string_field(const char* value,
                             size_t size) {
  if (!_internal_has_string_field()) {
    clear_foo();
    set_has_string_field();
    foo_.string_field_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  }
  foo_.string_field_.Set(
      ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size),
      GetArena());
  // @@protoc_insertion_point(field_set_pointer:protobuf_unittest.TestOptimizedForSize.string_field)
}
inline std::string* TestOptimizedForSize::_internal_mutable_string_field() {
  if (!_internal_has_string_field()) {
    clear_foo();
    set_has_string_field();
    foo_.string_field_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  }
  return foo_.string_field_.Mutable(
      ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* TestOptimizedForSize::release_string_field() {
  // @@protoc_insertion_point(field_release:protobuf_unittest.TestOptimizedForSize.string_field)
  if (_internal_has_string_field()) {
    clear_has_foo();
    return foo_.string_field_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  } else {
    return nullptr;
  }
}
inline void TestOptimizedForSize::set_allocated_string_field(std::string* string_field) {
  if (has_foo()) {
    clear_foo();
  }
  if (string_field != nullptr) {
    set_has_string_field();
    foo_.string_field_.UnsafeSetDefault(string_field);
    ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena();
    if (arena != nullptr) {
      arena->Own(string_field);
    }
  }
  // @@protoc_insertion_point(field_set_allocated:protobuf_unittest.TestOptimizedForSize.string_field)
}

inline bool TestOptimizedForSize::has_foo() const {
  return foo_case() != FOO_NOT_SET;
}
inline void TestOptimizedForSize::clear_has_foo() {
  _oneof_case_[0] = FOO_NOT_SET;
}
inline TestOptimizedForSize::FooCase TestOptimizedForSize::foo_case() const {
  return TestOptimizedForSize::FooCase(_oneof_case_[0]);
}
// -------------------------------------------------------------------

// TestRequiredOptimizedForSize

// required int32 x = 1;
inline bool TestRequiredOptimizedForSize::_internal_has_x() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool TestRequiredOptimizedForSize::has_x() const {
  return _internal_has_x();
}
inline void TestRequiredOptimizedForSize::clear_x() {
  x_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 TestRequiredOptimizedForSize::_internal_x() const {
  return x_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 TestRequiredOptimizedForSize::x() const {
  // @@protoc_insertion_point(field_get:protobuf_unittest.TestRequiredOptimizedForSize.x)
  return _internal_x();
}
inline void TestRequiredOptimizedForSize::_internal_set_x(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000001u;
  x_ = value;
}
inline void TestRequiredOptimizedForSize::set_x(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_x(value);
  // @@protoc_insertion_point(field_set:protobuf_unittest.TestRequiredOptimizedForSize.x)
}

// -------------------------------------------------------------------

// TestOptionalOptimizedForSize

// optional .protobuf_unittest.TestRequiredOptimizedForSize o = 1;
inline bool TestOptionalOptimizedForSize::_internal_has_o() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || o_ != nullptr);
  return value;
}
inline bool TestOptionalOptimizedForSize::has_o() const {
  return _internal_has_o();
}
inline void TestOptionalOptimizedForSize::clear_o() {
  if (o_ != nullptr) o_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::protobuf_unittest::TestRequiredOptimizedForSize& TestOptionalOptimizedForSize::_internal_o() const {
  const ::protobuf_unittest::TestRequiredOptimizedForSize* p = o_;
  return p != nullptr ? *p : reinterpret_cast<const ::protobuf_unittest::TestRequiredOptimizedForSize&>(
      ::protobuf_unittest::_TestRequiredOptimizedForSize_default_instance_);
}
inline const ::protobuf_unittest::TestRequiredOptimizedForSize& TestOptionalOptimizedForSize::o() const {
  // @@protoc_insertion_point(field_get:protobuf_unittest.TestOptionalOptimizedForSize.o)
  return _internal_o();
}
inline void TestOptionalOptimizedForSize::unsafe_arena_set_allocated_o(
    ::protobuf_unittest::TestRequiredOptimizedForSize* o) {
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(o_);
  }
  o_ = o;
  if (o) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:protobuf_unittest.TestOptionalOptimizedForSize.o)
}
inline ::protobuf_unittest::TestRequiredOptimizedForSize* TestOptionalOptimizedForSize::release_o() {
  _has_bits_[0] &= ~0x00000001u;
  ::protobuf_unittest::TestRequiredOptimizedForSize* temp = o_;
  o_ = nullptr;
  if (GetArena() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
  return temp;
}
inline ::protobuf_unittest::TestRequiredOptimizedForSize* TestOptionalOptimizedForSize::unsafe_arena_release_o() {
  // @@protoc_insertion_point(field_release:protobuf_unittest.TestOptionalOptimizedForSize.o)
  _has_bits_[0] &= ~0x00000001u;
  ::protobuf_unittest::TestRequiredOptimizedForSize* temp = o_;
  o_ = nullptr;
  return temp;
}
inline ::protobuf_unittest::TestRequiredOptimizedForSize* TestOptionalOptimizedForSize::_internal_mutable_o() {
  _has_bits_[0] |= 0x00000001u;
  if (o_ == nullptr) {
    auto* p = CreateMaybeMessage<::protobuf_unittest::TestRequiredOptimizedForSize>(GetArena());
    o_ = p;
  }
  return o_;
}
inline ::protobuf_unittest::TestRequiredOptimizedForSize* TestOptionalOptimizedForSize::mutable_o() {
  // @@protoc_insertion_point(field_mutable:protobuf_unittest.TestOptionalOptimizedForSize.o)
  return _internal_mutable_o();
}
inline void TestOptionalOptimizedForSize::set_allocated_o(::protobuf_unittest::TestRequiredOptimizedForSize* o) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  if (message_arena == nullptr) {
    delete o_;
  }
  if (o) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      ::PROTOBUF_NAMESPACE_ID::Arena::GetArena(o);
    if (message_arena != submessage_arena) {
      o = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, o, submessage_arena);
    }
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  o_ = o;
  // @@protoc_insertion_point(field_set_allocated:protobuf_unittest.TestOptionalOptimizedForSize.o)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf_unittest

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5foptimize_5ffor_2eproto
