// Copyright NVIDIA Corporation 2012
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#include <dp/Types.h>
#include <dp/fx/EnumSpec.h>
#include <algorithm>

namespace dp
{
  namespace fx
  {

    EnumSpecSharedPtr EnumSpec::create(std::string const& type , std::vector<std::string> const& values)
    {
      return( std::shared_ptr<EnumSpec>( new EnumSpec( type, values ) ) );
    }

    EnumSpec::EnumSpec(std::string const& type , std::vector<std::string> const& values)
      : m_type(type)
      , m_values(values)
    {
      DP_ASSERT( m_values.size() < dp::checked_cast<size_t>(std::numeric_limits<StorageType>::max()) );
    }

    EnumSpec::~EnumSpec()
    {
    }

    std::string const& EnumSpec::getType() const
    {
      return( m_type );
    }

    unsigned int EnumSpec::getValueCount() const
    {
      return(dp::checked_cast<unsigned int>(m_values.size()));
    }

    EnumSpec::StorageType EnumSpec::getValue( std::string const& name ) const
    {
      std::vector<std::string>::const_iterator it = std::find( m_values.begin(), m_values.end(), name );
      return((it == m_values.end()) ? ~0 : dp::checked_cast<StorageType>(distance(m_values.begin(), it)));
    }

    std::string const& EnumSpec::getValueName( unsigned int idx ) const
    {
      DP_ASSERT(dp::checked_cast<size_t>(idx) < m_values.size());
      return( m_values[idx] );
    }

    bool EnumSpec::isEquivalent( const EnumSpecSharedPtr & p, bool /*ignoreNames*/, bool /*deepCompare*/ ) const
    {
      if ( p == this )
      {
        return( true );
      }

      bool equivalent = m_values.size() == p->m_values.size();
      for ( size_t index = 0;equivalent && index < m_values.size(); ++index )
      {
        equivalent = m_values[index] == p->m_values[index];
      }
      return equivalent;
    }

  } // namespace fx
} // namespace cp
